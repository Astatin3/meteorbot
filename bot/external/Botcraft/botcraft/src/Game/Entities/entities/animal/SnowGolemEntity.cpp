#include "botcraft/Game/Entities/entities/animal/SnowGolemEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, SnowGolemEntity::metadata_count> SnowGolemEntity::metadata_names{ {
        "data_pumpkin_id",
    } };

    SnowGolemEntity::SnowGolemEntity()
    {
        // Initialize all metadata with default values
        SetDataPumpkinId(16);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 4.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
    }

    SnowGolemEntity::~SnowGolemEntity()
    {

    }


    std::string SnowGolemEntity::GetName() const
    {
        return "snow_golem";
    }

    EntityType SnowGolemEntity::GetType() const
    {
        return EntityType::SnowGolem;
    }


    std::string SnowGolemEntity::GetClassName()
    {
        return "snow_golem";
    }

    EntityType SnowGolemEntity::GetClassType()
    {
        return EntityType::SnowGolem;
    }


    ProtocolCraft::Json::Value SnowGolemEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractGolemEntity::Serialize();

        output["metadata"]["data_pumpkin_id"] = GetDataPumpkinId();

        return output;
    }


    void SnowGolemEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char SnowGolemEntity::GetDataPumpkinId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_pumpkin_id"));
    }


    void SnowGolemEntity::SetDataPumpkinId(const char data_pumpkin_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_pumpkin_id"] = data_pumpkin_id;
    }


    double SnowGolemEntity::GetWidthImpl() const
    {
        return 0.7;
    }

    double SnowGolemEntity::GetHeightImpl() const
    {
        return 1.9;
    }

}
