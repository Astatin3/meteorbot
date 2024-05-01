#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class ZombieHorseEntity : public AbstractHorseEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        ZombieHorseEntity();
        virtual ~ZombieHorseEntity();

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
