#pragma once

#include "botcraft/Game/Entities/entities/projectile/FireballEntity.hpp"

namespace Botcraft
{
    class LargeFireballEntity : public FireballEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = FireballEntity::metadata_count + FireballEntity::hierarchy_metadata_count;

    public:
        LargeFireballEntity();
        virtual ~LargeFireballEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
