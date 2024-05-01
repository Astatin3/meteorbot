#pragma once

#if PROTOCOL_VERSION < 461 /* < 1.14 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundUseBedPacket : public BaseMessage<ClientboundUseBedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x33;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Use Bed";

        virtual ~ClientboundUseBedPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }


        int GetEntityId() const
        {
            return entity_id;
        }

        const NetworkPosition& GetLocation() const
        {
            return location;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
            location = ReadData<NetworkPosition>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<NetworkPosition>(location, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
            output["location"] = location;

            return output;
        }

    private:
        int entity_id = 0;
        NetworkPosition location;

    };
} //ProtocolCraft
#endif
