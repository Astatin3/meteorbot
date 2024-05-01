#pragma once

#include "botcraft/Game/Entities/entities/projectile/ThrowableItemProjectileEntity.hpp"

namespace Botcraft
{
    class ThrownEggEntity : public ThrowableItemProjectileEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ThrowableItemProjectileEntity::metadata_count + ThrowableItemProjectileEntity::hierarchy_metadata_count;

    public:
        ThrownEggEntity();
        virtual ~ThrownEggEntity();

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
