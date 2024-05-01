#pragma once

#include "botcraft/Game/Entities/entities/MobEntity.hpp"

namespace Botcraft
{
    class EnderDragonEntity : public MobEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;

    public:
        EnderDragonEntity();
        virtual ~EnderDragonEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataPhase() const;

        void SetDataPhase(const int data_phase);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
