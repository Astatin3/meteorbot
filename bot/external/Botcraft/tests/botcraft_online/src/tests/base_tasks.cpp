#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/AI/Tasks/BaseTasks.hpp>

#include <sstream>

TEST_CASE("say")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    bot->SyncAction(5000, Botcraft::Say, "Hello, world!");
    const std::string& botname = bot->GetNetworkManager()->GetMyName();

    REQUIRE_NOTHROW(MinecraftServer::GetInstance().WaitLine(".*: (?:\\[Not Secure\\] )?[[<]" + botname + "[>\\]] Hello, world!.*", 5000));
}

bool IsLitRedstoneLamp(const Botcraft::Blockstate* block)
{
    if (block == nullptr)
    {
        return false;
    }
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    return block->GetName() == "minecraft:redstone_lamp" && block->GetVariableValue("lit") == "true";
#else
    return block->GetName() == "minecraft:lit_redstone_lamp";
#endif
}

TEST_CASE("interact")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    const Botcraft::Position lever = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 1, 1);
    const Botcraft::Position lamp = lever - Botcraft::Position(0, 1, 0);

    // Wait for at least one tick because otherwise for some versions the server sometimes
    // does not register the new position (? not sure about what happens here)
    Botcraft::Utilities::WaitForCondition([]() -> bool
        {
            return false;
        }, 100);

    bot->SyncAction(5000, Botcraft::InteractWithBlock, lever, Botcraft::PlayerDiggingFace::Up, true);

    std::shared_ptr<Botcraft::World> world = bot->GetWorld();

    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            const Botcraft::Blockstate* block = world->GetBlock(lamp);
            return IsLitRedstoneLamp(block);
        }, 5000));
}

TEST_CASE("get day time")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    auto day_time = GENERATE(1000, 5000, 10000, 15000, 20000, 23500);

    // Sent time set command
    MinecraftServer::GetInstance().SendLine("time set " + std::to_string(day_time));
    MinecraftServer::GetInstance().WaitLine(".*: Set the time to " + std::to_string(day_time) + ".*", 5000);

    Botcraft::Utilities::WaitForCondition([&]()
    {
        return bot->GetDayTime() == day_time;
    }, 5000);
    CHECK(bot->GetDayTime() == day_time);

    // Reset the time to day
    MinecraftServer::GetInstance().SendLine("time set day");
    MinecraftServer::GetInstance().WaitLine(".*: Set the time to 1000.*", 5000);
}
