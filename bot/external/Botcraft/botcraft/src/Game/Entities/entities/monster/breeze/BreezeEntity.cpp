#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "botcraft/Game/Entities/entities/monster/breeze/BreezeEntity.hpp"

#include <mutex>

namespace Botcraft
{
    BreezeEntity::BreezeEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.6) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 30.0) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 24.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
    }

    BreezeEntity::~BreezeEntity()
    {

    }


    std::string BreezeEntity::GetName() const
    {
        return "breeze";
    }

    EntityType BreezeEntity::GetType() const
    {
        return EntityType::Breeze;
    }


    std::string BreezeEntity::GetClassName()
    {
        return "breeze";
    }

    EntityType BreezeEntity::GetClassType()
    {
        return EntityType::Breeze;
    }


    double BreezeEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double BreezeEntity::GetHeightImpl() const
    {
        return 1.7;
    }

}
#endif
