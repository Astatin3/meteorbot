#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayObjectivePacket : public BaseMessage<ClientboundSetDisplayObjectivePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x55;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Display Objective";

        virtual ~ClientboundSetDisplayObjectivePacket() override
        {

        }

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
       void SetSlot(const char slot_)
        {
            slot = slot_;
        }
#else
        void SetSlot(const int slot_)
        {
            slot = slot_;
        }
#endif

        void SetObjectiveName(const std::string& objective_name_)
        {
            objective_name = objective_name_;
        }


#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        char GetSlot() const
        {
            return slot;
        }
#else
        int GetSlot() const
        {
            return slot;
        }
#endif

        const std::string& GetObjectiveName() const
        {
            return objective_name;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            slot = ReadData<char>(iter, length);
#else
            slot = ReadData<VarInt>(iter, length);
#endif
            objective_name = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<char>(slot, container);
#else
            WriteData<VarInt>(slot, container);
#endif
            WriteData<std::string>(objective_name, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["slot"] = slot;
            output["objective_name"] = objective_name;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        char slot = 0;
#else
        int slot = 0;
#endif
        std::string objective_name;

    };
} //ProtocolCraft
