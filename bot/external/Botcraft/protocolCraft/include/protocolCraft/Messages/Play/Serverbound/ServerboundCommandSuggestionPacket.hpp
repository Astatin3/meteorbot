#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundCommandSuggestionPacket : public BaseMessage<ServerboundCommandSuggestionPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x0A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Command Suggestion";

        virtual ~ServerboundCommandSuggestionPacket() override
        {

        }

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
        void SetId_(const int id__)
        {
            id_ = id__;
        }
#endif

        void SetCommand(const std::string& command_)
        {
            command = command_;
        }

#if PROTOCOL_VERSION < 345 /* < 1.13 */
        void SetAssumeCommand(const bool assume_command_)
        {
            assume_command = assume_command_;
        }

        void SetLookedAtBlock(const std::optional<NetworkPosition>& looked_at_block_)
        {
            looked_at_block = looked_at_block_;
        }
#endif


#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
        int GetId_() const
        {
            return id_;
        }
#endif

        const std::string& GetCommand() const
        {
            return command;
        }

#if PROTOCOL_VERSION < 345 /* < 1.13 */
        bool GetAssumeCommand() const
        {
            return assume_command;
        }

        const std::optional<NetworkPosition>& GetLookedAtBlock() const
        {
            return looked_at_block;
        }
#endif



    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
            id_ = ReadData<VarInt>(iter, length);
#endif
            command = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION < 345 /* < 1.13 */
            assume_command = ReadData<bool>(iter, length);
            looked_at_block = ReadOptional<NetworkPosition>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
            WriteData<VarInt>(id_, container);
#endif
            WriteData<std::string>(command, container);
#if PROTOCOL_VERSION < 345 /* < 1.13 */
            WriteData<bool>(assume_command, container);
            WriteOptional<NetworkPosition>(looked_at_block, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
            output["id_"] = id_;
#endif
            output["command"] = command;
#if PROTOCOL_VERSION < 345 /* < 1.13 */
            output["assume_command"] = assume_command;
            if (looked_at_block.has_value())
            {
                output["looked_at_block"] = looked_at_block.value();
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
        int id_ = 0;
#endif
        std::string command;
#if PROTOCOL_VERSION < 345 /* < 1.13 */
        bool assume_command = false;
        std::optional<NetworkPosition> looked_at_block;
#endif

    };
} //ProtocolCraft
