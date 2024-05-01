#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundHelloPacket : public BaseMessage<ServerboundHelloPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Hello";

        virtual ~ServerboundHelloPacket() override
        {

        }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        void SetName(const std::string& name__)
        {
            name_ = name__;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetPublicKey(const std::optional<ProfilePublicKey>& public_key_)
        {
            public_key = public_key_;
        }
#endif

#if PROTOCOL_VERSION > 759 /* > 1.19 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetProfileId(const std::optional<UUID>& profile_id_)
        {
            profile_id = profile_id_;
        }
#else
        void SetProfileId(const UUID& profile_id_)
        {
            profile_id = profile_id_;
        }
#endif
#endif

        const std::string& GetName_() const
        {
            return name_;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        const std::optional<ProfilePublicKey>& GetPublicKey() const
        {
            return public_key;
        }
#endif

#if PROTOCOL_VERSION > 759 /* > 1.19 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        const std::optional<UUID>& GetProfileId() const
        {
            return profile_id;
        }
#else
        const UUID& GetProfileId() const
        {
            return profile_id;
        }
#endif
#endif
#else
        void SetGameProfile(const std::string& n)
        {
            game_profile = n;
        }

        const std::string& GetGameProfile() const
        {
            return game_profile;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            name_ = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            public_key = ReadOptional<ProfilePublicKey>(iter, length);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            profile_id = ReadOptional<UUID>(iter, length);
#else
            profile_id = ReadData<UUID>(iter, length);
#endif
#endif
#else
            game_profile = ReadData<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            WriteData<std::string>(name_, container);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteOptional<ProfilePublicKey>(public_key, container);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteOptional<UUID>(profile_id, container);
#else
            WriteData<UUID>(profile_id, container);
#endif
#endif
#else
            WriteData<std::string>(game_profile, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            output["name"] = name_;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            if (public_key.has_value())
            {
                output["public_key"] = public_key.value();
            }
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            if (profile_id.has_value())
            {
                output["profile_id"] = profile_id.value();
            }
#else
            output["profile_id"] = profile_id;
#endif
#endif
#else
            output["game_profile"] = game_profile;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        std::string name_;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        std::optional<ProfilePublicKey> public_key;
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */ 
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        std::optional<UUID> profile_id;
#else
        UUID profile_id = {};
#endif
#endif
#else
        std::string game_profile;
#endif
    };
} // ProtocolCraft
