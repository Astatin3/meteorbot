#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/monster/DrownedEntity.hpp"

namespace Botcraft
{
    DrownedEntity::DrownedEntity()
    {

    }

    DrownedEntity::~DrownedEntity()
    {

    }


    std::string DrownedEntity::GetName() const
    {
        return "drowned";
    }

    EntityType DrownedEntity::GetType() const
    {
        return EntityType::Drowned;
    }


    std::string DrownedEntity::GetClassName()
    {
        return "drowned";
    }

    EntityType DrownedEntity::GetClassType()
    {
        return EntityType::Drowned;
    }


    double DrownedEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double DrownedEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
