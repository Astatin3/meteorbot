#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class EndCrystalEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        EndCrystalEntity();
        virtual ~EndCrystalEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        std::optional<Position> GetDataBeamTarget() const;
        bool GetDataShowBottom() const;

        void SetDataBeamTarget(const std::optional<Position>& data_beam_target);
        void SetDataShowBottom(const bool data_show_bottom);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
