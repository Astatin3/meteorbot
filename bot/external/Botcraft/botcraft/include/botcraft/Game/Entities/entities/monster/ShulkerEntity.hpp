#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractGolemEntity.hpp"

namespace Botcraft
{
    class ShulkerEntity : public AbstractGolemEntity
    {
    protected:
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 4;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractGolemEntity::metadata_count + AbstractGolemEntity::hierarchy_metadata_count;

    public:
        ShulkerEntity();
        virtual ~ShulkerEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        Direction GetDataAttachFaceId() const;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        std::optional<Position> GetDataAttachPosId() const;
#endif
        char GetDataPeekId() const;
        char GetDataColorId() const;

        void SetDataAttachFaceId(const Direction data_attach_face_id);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetDataAttachPosId(const std::optional<Position>& data_attach_pos_id);
#endif
        void SetDataPeekId(const char data_peek_id);
        void SetDataColorId(const char data_color_id);

        // Attribute stuff
        // 7e0292f2-9434-48d5-a29f-9583af7df27f
        static constexpr std::array<unsigned char, 16> covered_armor_modifier_uuid = { 0x7E, 0x2, 0x92, 0xF2, 0x94, 0x34, 0x48, 0xD5, 0xA2, 0x9F, 0x95, 0x83, 0xAF, 0x7D, 0xF2, 0x7F };


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
