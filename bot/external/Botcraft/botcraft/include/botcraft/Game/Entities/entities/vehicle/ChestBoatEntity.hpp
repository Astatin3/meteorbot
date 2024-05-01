#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "botcraft/Game/Entities/entities/vehicle/BoatEntity.hpp"

namespace Botcraft
{
    class ChestBoatEntity : public BoatEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = BoatEntity::metadata_count + BoatEntity::hierarchy_metadata_count;

    public:
        ChestBoatEntity();
        virtual ~ChestBoatEntity();

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
#endif
