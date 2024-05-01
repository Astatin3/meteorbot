#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class EnderManEntity : public MonsterEntity
    {
    protected:
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 2;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        EnderManEntity();
        virtual ~EnderManEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataCarryState() const;
        bool GetDataCreepy() const;
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        bool GetDataStaredAt() const;
#endif

        void SetDataCarryState(const int data_carry_state);
        void SetDataCreepy(const bool data_creepy);
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        void SetDataStaredAt(const bool data_stared_at);
#endif

        // Attribute stuff
        // 020e0dfb-87ae-4653-9556-831010e291a0
        static constexpr std::array<unsigned char, 16> speed_modifier_attacking_uuid = { 0x2, 0xE, 0xD, 0xFB, 0x87, 0xAE, 0x46, 0x53, 0x95, 0x56, 0x83, 0x10, 0x10, 0xE2, 0x91, 0xA0 };


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
