#pragma once

#include "botcraft/Game/Entities/entities/monster/GuardianEntity.hpp"

namespace Botcraft
{
    class ElderGuardianEntity : public GuardianEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = GuardianEntity::metadata_count + GuardianEntity::hierarchy_metadata_count;

    public:
        ElderGuardianEntity();
        virtual ~ElderGuardianEntity();

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
