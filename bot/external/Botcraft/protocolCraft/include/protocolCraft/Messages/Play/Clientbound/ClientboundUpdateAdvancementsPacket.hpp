#pragma once

#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Advancement.hpp"
#include "protocolCraft/Types/AdvancementProgress.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAdvancementsPacket : public BaseMessage<ClientboundUpdateAdvancementsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x64;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x69;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x6C;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x70;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Advancements";

        virtual ~ClientboundUpdateAdvancementsPacket() override
        {

        }

        void SetReset(const bool reset_)
        {
            reset = reset_;
        }

        void SetAdded(const std::map<Identifier, Advancement>& added_)
        {
            added = added_;
        }

        void SetRemoved(const std::vector<Identifier>& removed_)
        {
            removed = removed_;
        }

        void SetProgress(const std::map<Identifier, AdvancementProgress>& progress_)
        {
            progress = progress_;
        }


        bool GetReset() const
        {
            return reset;
        }

        const std::map<Identifier, Advancement>& GetAdded() const
        {
            return added;
        }

        const std::vector<Identifier>& GetRemoved() const
        {
            return removed;
        }

        const std::map<Identifier, AdvancementProgress>& GetProgress() const
        {
            return progress;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            reset = ReadData<bool>(iter, length);
            added = ReadMap<Identifier, Advancement>(iter, length);
            removed = ReadVector<Identifier>(iter, length);
            progress = ReadMap<Identifier, AdvancementProgress, VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(reset, container);
            WriteMap<Identifier, Advancement>(added, container);
            WriteVector<Identifier>(removed, container);
            WriteMap<Identifier, AdvancementProgress>(progress, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["reset"] = reset;

            output["added"] = Json::Array();
            for (const auto& p : added)
            {
                output["added"].push_back({ {"key", p.first}, {"value", p.second} });
            }

            output["removed"] = removed;

            output["progress"] = Json::Array();
            for (const auto& p : progress)
            {
                output["progress"].push_back({ {"key", p.first}, {"value", p.second} });
            }

            return output;
        }

    private:
        bool reset = false;
        std::map<Identifier, Advancement> added;
        std::vector<Identifier> removed;
        std::map<Identifier, AdvancementProgress> progress;

    };
} //ProtocolCraft
