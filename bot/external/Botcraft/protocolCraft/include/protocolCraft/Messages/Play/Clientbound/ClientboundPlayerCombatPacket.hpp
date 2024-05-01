#pragma once

#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatPacket : public BaseMessage<ClientboundPlayerCombatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x31;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Combat";

        virtual ~ClientboundPlayerCombatPacket() override
        {

        }

        void SetEvent(const int event__)
        {
            event_ = event__;
        }

        void SetPlayerId(const int player_id_)
        {
            player_id = player_id_;
        }

        void SetKillerId(const int killer_id_)
        {
            killer_id = killer_id_;
        }

        void SetDuration(const int duration_)
        {
            duration = duration_;
        }

        void SetMessage(const Chat& message_)
        {
            message = message_;
        }


        int GetEvent() const
        {
            return event_;
        }

        int GetPlayerId() const
        {
            return player_id;
        }

        int GetKillerId() const
        {
            return killer_id;
        }

        int GetDuration() const
        {
            return duration;
        }

        const Chat& GetMessage() const
        {
            return message;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            event_ = ReadData<VarInt>(iter, length);

            if (event_ == 1)
            {
                duration = ReadData<VarInt>(iter, length);
                killer_id = ReadData<int>(iter, length);
            }
            else if (event_ == 2)
            {
                player_id = ReadData<VarInt>(iter, length);
                killer_id = ReadData<int>(iter, length);
                message = ReadData<Chat>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(event_, container);
            if (event_ == 1)
            {
                WriteData<VarInt>(duration, container);
                WriteData<int>(killer_id, container);
            }
            else if (event_ == 2)
            {
                WriteData<VarInt>(player_id, container);
                WriteData<int>(killer_id, container);
                WriteData<Chat>(message, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["event"] = event_;
            if (event_ == 1)
            {
                output["duration"] = duration;
                output["killer_id"] = killer_id;
            }
            else if (event_ == 2)
            {
                output["player_id"] = player_id;
                output["killer_id"] = killer_id;
                output["message"] = message;
            }

            return output;
        }

    private:
        int event_ = 0;
        int player_id = 0;
        int killer_id = 0;
        int duration = 0;
        Chat message;

    };
} //ProtocolCraft
#endif
