#include "MinecraftServer.hpp"

#include <subprocess/subprocess.h>

#include <botcraft/Utilities/Logger.hpp>
#include <botcraft/Utilities/SleepUtilities.hpp>
#include <botcraft/Version.hpp>

#include <stdexcept>
#include <array>
#include <regex>
#include <fstream>

const std::filesystem::path server_relative_files_path = "../../test_server_files";

MinecraftServerOptions MinecraftServer::options;

MinecraftServer::MinecraftServer()
{
    running = false;
    const std::filesystem::path current_path = std::filesystem::current_path();
    const std::filesystem::path exe_path = std::filesystem::path(options.argv0).is_absolute() ? std::filesystem::path(options.argv0) : (current_path / options.argv0);
    server_path = exe_path.parent_path() / "test_servers" / game_version;

    if (std::filesystem::exists(server_path))
    {
        std::filesystem::remove_all(server_path);
    }
    std::filesystem::create_directories(server_path);

    server_path = std::filesystem::canonical(server_path);
    InitServerFolder(server_path);

    // Change current path to launch server in the dedicated folder
    std::filesystem::current_path(server_path);
    const std::string jar_path = (server_relative_files_path / "server_jars" / ("server_" + game_version + ".jar")).string();
    const char* command_line[] = { "java", "-Xmx1024M", "-Xms1024M", "-jar", jar_path.c_str(), "nogui", NULL};

    subprocess = std::make_unique<subprocess_s>();
    int result = subprocess_create(command_line,
        subprocess_option_combined_stdout_stderr |
        subprocess_option_inherit_environment |
        subprocess_option_enable_async |
        subprocess_option_no_window |
        subprocess_option_search_user_path,
        subprocess.get()
    );
    // Restore current path to previous value
    std::filesystem::current_path(current_path);
    if (result != 0)
    {
        LOG_FATAL("Error starting wrapped server process");
        throw std::runtime_error("Error starting wrapped server process");
    }
    running = true;
    read_thread = std::thread(&MinecraftServer::InternalThreadRead, this);
}

MinecraftServer::~MinecraftServer()
{
    // Ask the server to stop properly
    SendLine("stop");

    // Wait for the process to finish
    if (subprocess_join(subprocess.get(), NULL) != 0)
    {
        LOG_FATAL("Error joining wrapped server process, killing it");
        Kill();
    }
    running = false;
    if (subprocess_destroy(subprocess.get()) != 0)
    {
        LOG_FATAL("Error destroying wrapped server process");
    }
    subprocess.reset();
    if (read_thread.joinable())
    {
        read_thread.join();
    }
}

MinecraftServer& MinecraftServer::GetInstance()
{
    static MinecraftServer instance;
    return instance;
}

void MinecraftServer::Initialize()
{
    if (!running)
    {
        LOG_WARNING("Trying to initialize a server that is not running");
        return;
    }

    // Make sure the server is running and ready
    // (5 minutes should be enough for the server to start even on a potato)
    WaitLine(".*: Done \\([\\d.,]+s\\)! For help, type \"help\".*", 300000);

    // Set gamerules
    InitServerGamerules();

    // Set time to day
    SendLine("time set day");
    WaitLine(".*: Set the time to \\d+.*", 5000);
}

std::string MinecraftServer::WaitLine(const long long int timeout_ms)
{
    return WaitLine("", timeout_ms)[0];
}

std::vector<std::string> MinecraftServer::WaitLine(const std::string& regex, const long long int timeout_ms)
{
    if (!running)
    {
        return { "" };
    }

    std::chrono::steady_clock::time_point time_check = std::chrono::steady_clock::now();
    const std::chrono::steady_clock::time_point start = time_check;
    std::vector<std::string> output;
    if (Botcraft::Utilities::WaitForCondition([&]()
        {
            std::unique_lock<std::mutex> lock(internal_read_mutex);
            if (lines.size() > 0)
            {
                const std::string line = lines.front();
                lines.pop();
                if (regex.empty())
                {
                    LOG_DEBUG("Line caught (no regex):\n" << line);
                    output = { line };
                    return true;
                }
                std::smatch match;
                if (std::regex_match(line, match, std::regex(regex)))
                {
                    output.resize(match.size());
                    for (size_t i = 0; i < match.size(); ++i)
                    {
                        output[i] = match[i].str();
                    }
                    LOG_DEBUG("Line caught using regex [" << regex << "]:\n" << line);
                    return true;
                }
            }
            if (timeout_ms == 0)
            {
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(now - time_check).count() > 30)
                {
                    time_check = now;
                    LOG_WARNING("Waiting for a server line matching [" << regex << "] since " << std::chrono::duration_cast<std::chrono::seconds>(now - start).count() << " seconds. Infinite loop?");
                }
            }
            return false;
        }, timeout_ms))
    {
        return output;
    }

    if (regex.empty())
    {
        LOG_FATAL("Timeout waiting for server to output a line");
        throw std::runtime_error("Timeout waiting for server to output a line");
    }
    else
    {
        LOG_FATAL("Timeout waiting for server to output a line matching [" << regex << "]");
        throw std::runtime_error("Timeout waiting for server to output a line matching [" + regex + "]");
    }
}

void MinecraftServer::SendLine(const std::string& input)
{
    if (!running)
    {
        return;
    }

    FILE* p_stdin = subprocess_stdin(subprocess.get());
    LOG_DEBUG("Sending to server:\n" << input);
    std::fputs(input.back() == '\n' ? input.c_str() : (input + '\n').c_str(), p_stdin);
    std::fflush(p_stdin);
}

std::filesystem::path MinecraftServer::GetStructurePath() const
{
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    return server_path / "world" / "generated" / "minecraft" / "structures";
#else
    return server_path / "world" / "structures";
#endif
}

void MinecraftServer::Kill()
{
    int result = subprocess_terminate(subprocess.get());
    if (result != 0)
    {
        LOG_FATAL("Error killing wrapped server process");
    }
    running = false;
}

void MinecraftServer::InternalThreadRead()
{
    Botcraft::Logger::GetInstance().RegisterThread("read");
    std::array<char, 256> buffer;
    std::string line = "";
    unsigned int bytes_read = 0;
    while ((bytes_read = subprocess_read_stdout(subprocess.get(), buffer.data(), sizeof(buffer))))
    {
        line += std::string(buffer.data(), bytes_read);
        // Remove windows \r stuff if any
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        size_t newline_pos = 0;
        while ((newline_pos = line.find('\n')) != std::string::npos)
        {
            std::unique_lock<std::mutex> lock(internal_read_mutex);
            lines.push(line.substr(0, newline_pos));
            LOG_DEBUG("[SERVER] - " << lines.back());
            line = line.substr(newline_pos + 1);
        }
    }
}

void MinecraftServer::InitServerFolder(const std::filesystem::path& path)
{
    // Bash script to relaunch the server manually
#if _WIN32
    if (std::ofstream bash = std::ofstream(path / "start.cmd"))
#else
    if (std::ofstream bash = std::ofstream(path / "start.sh"))
#endif
    {
        bash << "java -Xmx1024M -Xms1024M -jar " << server_relative_files_path.string() << "/server_jars/server_" << game_version << ".jar nogui\n";
    }
    else
    {
        LOG_FATAL("Unable to create start bash script");
        throw std::runtime_error("Unable to create start bash script");
    }

    // Accept the EULA
    if (std::ofstream eula = std::ofstream(path / "eula.txt"))
    {
        eula << "eula=true\n";
    }
    else
    {
        LOG_FATAL("Unable to create eula.txt");
        throw std::runtime_error("Unable to create eula.txt");
    }

    // Setting the value of all non default properties
    if (std::ofstream server_props = std::ofstream(path / "server.properties"))
    {
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        server_props << "difficulty=3" << "\n";
#else
        server_props << "difficulty=hard" << "\n";
#endif
        server_props << "enable-command-block=true" << "\n";
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        server_props << "enforce-secure-profile=false" << "\n";
#endif
        // Everyone joins as creative and bots will be manually set to survival upon join
        server_props << "force-gamemode=true" << "\n";
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        server_props << "gamemode=1" << "\n";
#else
        server_props << "gamemode=creative" << "\n";
#endif
        server_props << "generate-structures=false" << "\n";
        // generator-settings should be there but it doesn't work on all
        // supported versions see https://bugs.mojang.com/browse/MC-195468
        // Set using custom level.dat file instead
        server_props << "level-seed=botcraft" << "\n";
        server_props << "level-type=flat" << "\n";
        server_props << "motd=Botcraft test server" << "\n";
#if USE_COMPRESSION
        server_props << "network-compression-threshold=256" << "\n";
#else
        // This should technically never happen as we need
        // compression support for protocolCraft to read
        // structures NBT files
        server_props << "network-compression-threshold=-1" << "\n";
#endif
        server_props << "online-mode=false" << "\n";
        server_props << "spawn-monsters=false" << "\n";
        server_props << "spawn-protection=0" << "\n";
        server_props << "view-distance=" << options.view_distance << "\n";
    }
    else
    {
        LOG_FATAL("Unable to create server.properties");
        throw std::runtime_error("Unable to create server.properties");
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    std::filesystem::create_directories(path / "world" / "generated" / "minecraft");
#else
    std::filesystem::create_directories(path / "world");
#endif

    // Setup level.dat
    std::filesystem::copy_file(path / server_relative_files_path / "runtime" / "level.dat", path / "world" / "level.dat");

    // Setup structures files
    std::filesystem::copy(
        path / server_relative_files_path / "runtime" / "structures",
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        path / "world" / "generated" / "minecraft" / "structures",
#else
        path / "world" / "structures",
#endif
        std::filesystem::copy_options::recursive);
}

void MinecraftServer::SetGamerule(const std::string& gamerule, const std::string& value)
{
    SendLine("gamerule " + gamerule + " " + value);
    WaitLine(".*: Game ?rule " + gamerule + " (?:is now set to:|has been updated to) " + value + ".*", 5000);
}

void MinecraftServer::InitServerGamerules()
{
    SetGamerule("announceAdvancements", "false");
#if PROTOCOL_VERSION > 485 /* > 1.14.2 */
    SetGamerule("disableRaids", "true");
#endif
    SetGamerule("doDaylightCycle", "false");
    SetGamerule("doFireTick", "false");
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    SetGamerule("doInsomnia", "false");
#endif
    SetGamerule("doMobSpawning", "false");
#if PROTOCOL_VERSION > 575 /* > 1.15.1 */
    SetGamerule("doPatrolSpawning", "false");
    SetGamerule("doTraderSpawning", "false");
#endif
    SetGamerule("doWeatherCycle", "false");
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    SetGamerule("doWardenSpawning", "false");
#endif
    SetGamerule("mobGriefing", "false");
    SetGamerule("randomTickSpeed", "0");
    SetGamerule("spawnRadius", "0");
    SetGamerule("spectatorsGenerateChunks", "true");
}
