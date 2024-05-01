#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <map>

namespace ProtocolCraft
{
    class ClientboundAwardStatsPacket : public BaseMessage<ClientboundAwardStatsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */ ||  \
      PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x04;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Award Stats";

        virtual ~ClientboundAwardStatsPacket() override
        {

        }

#if PROTOCOL_VERSION < 346 /* < 1.13 */
        void SetStats(const std::map<std::string, int>& stats_)
        {
            stats = stats_;
        }
#else
        void SetStats(const std::map<std::pair<int, int>, int>& stats_)
        {
            stats = stats_;
        }
#endif


#if PROTOCOL_VERSION < 346 /* < 1.13 */
        const std::map<std::string, int>& GetStats() const
        {
            return stats;
        }
#else
        const std::map<std::pair<int, int>, int>& GetStats() const
        {
            return stats;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

#if PROTOCOL_VERSION < 346 /* < 1.13 */
            stats = ReadMap<std::string, int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const std::string name = ReadData<std::string>(i, l);
                    const int val = ReadData<VarInt>(i, l);

                    return std::make_pair(name, val);
                }
            );
#else
            stats = ReadMap<std::pair<int, int>, int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const int category_id = ReadData<VarInt>(i, l);
                    const int stats_id = ReadData<VarInt>(i, l);
                    const int val = ReadData<VarInt>(i, l);

                    return std::make_pair(std::make_pair(category_id, stats_id), val);
                }
            );
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 346 /* < 1.13 */
            WriteMap<std::string, int>(stats, container,
                [](const std::pair<const std::string, int>& p, WriteContainer& c)
                {
                    WriteData<std::string>(p.first, c);
                    WriteData<VarInt>(p.second, c);
                }
            );
#else
            WriteMap<std::pair<int, int>, int>(stats, container,
                [](const std::pair<const std::pair<int, int>, int>& p, WriteContainer& c)
                {
                    WriteData<VarInt>(p.first.first, c);
                    WriteData<VarInt>(p.first.second, c);
                    WriteData<VarInt>(p.second, c);
                }
            );
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 346 /* < 1.13 */
            output["stats"] = stats;
#else
            output["stats"] = Json::Array();
            for (const auto& p : stats)
            {
                output.push_back({
                    {"category_id", p.first.first},
                    {"stats_id", p.first.second},
                    {"value", p.second} }
                );
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 346 /* < 1.13 */
        std::map<std::string, int> stats;
#else
        std::map<std::pair<int, int>, int> stats;
#endif

    };
} //ProtocolCraft
