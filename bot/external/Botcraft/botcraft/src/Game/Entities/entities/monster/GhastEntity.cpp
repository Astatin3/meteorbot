#include "botcraft/Game/Entities/entities/monster/GhastEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, GhastEntity::metadata_count> GhastEntity::metadata_names{ {
        "data_is_charging",
    } };

    GhastEntity::GhastEntity()
    {
        // Initialize all metadata with default values
        SetDataIsCharging(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 100.0) });
    }

    GhastEntity::~GhastEntity()
    {

    }


    std::string GhastEntity::GetName() const
    {
        return "ghast";
    }

    EntityType GhastEntity::GetType() const
    {
        return EntityType::Ghast;
    }


    std::string GhastEntity::GetClassName()
    {
        return "ghast";
    }

    EntityType GhastEntity::GetClassType()
    {
        return EntityType::Ghast;
    }


    ProtocolCraft::Json::Value GhastEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = FlyingMobEntity::Serialize();

        output["metadata"]["data_is_charging"] = GetDataIsCharging();

        return output;
    }


    void GhastEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            FlyingMobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool GhastEntity::GetDataIsCharging() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_is_charging"));
    }


    void GhastEntity::SetDataIsCharging(const bool data_is_charging)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_is_charging"] = data_is_charging;
    }


    double GhastEntity::GetWidthImpl() const
    {
        return 4.0;
    }

    double GhastEntity::GetHeightImpl() const
    {
        return 4.0;
    }

}
