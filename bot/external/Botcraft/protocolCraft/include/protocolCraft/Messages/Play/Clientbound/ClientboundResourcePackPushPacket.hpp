#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPushPacket : public BaseMessage<ClientboundResourcePackPushPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x44;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ressource Pack Push";

        virtual ~ClientboundResourcePackPushPacket() override
        {

        }

        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetUrl(const std::string& url_)
        {
            url = url_;
        }

        void SetHash(const std::string& hash_)
        {
            hash = hash_;
        }

        void SetRequired(const bool required_)
        {
            required = required_;
        }

        void SetPrompt(const std::optional<Chat>& prompt_)
        {
            prompt = prompt_;
        }


        const UUID& GetUUID() const
        {
            return uuid;
        }

        const std::string& GetUrl() const
        {
            return url;
        }

        const std::string& GetHash() const
        {
            return hash;
        }

        bool GetRequired() const
        {
            return required;
        }

        const std::optional<Chat>& GetPrompt() const
        {
            return prompt;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            uuid = ReadData<UUID>(iter, length);
            url = ReadData<std::string>(iter, length);
            hash = ReadData<std::string>(iter, length);
            required = ReadData<bool>(iter, length);
            prompt = ReadOptional<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<UUID>(uuid, container);
            WriteData<std::string>(url, container);
            WriteData<std::string>(hash, container);
            WriteData<bool>(required, container);
            WriteOptional<Chat>(prompt, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["uuid"] = uuid;
            output["url"] = url;
            output["hash"] = hash;
            output["required"] = required;
            if (prompt.has_value())
            {
                output["prompt"] = prompt.value();
            }

            return output;
        }

    private:
        UUID uuid = {};
        std::string url;
        std::string hash;
        bool required = false;
        std::optional<Chat> prompt;

    };
} //ProtocolCraft
#endif
