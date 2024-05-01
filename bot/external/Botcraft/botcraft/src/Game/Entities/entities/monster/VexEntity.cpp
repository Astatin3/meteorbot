#include "botcraft/Game/Entities/entities/monster/VexEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, VexEntity::metadata_count> VexEntity::metadata_names{ {
        "data_flags_id",
    } };

    VexEntity::VexEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 14.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 4.0) });
    }

    VexEntity::~VexEntity()
    {

    }


    std::string VexEntity::GetName() const
    {
        return "vex";
    }

    EntityType VexEntity::GetType() const
    {
        return EntityType::Vex;
    }


    std::string VexEntity::GetClassName()
    {
        return "vex";
    }

    EntityType VexEntity::GetClassType()
    {
        return EntityType::Vex;
    }


    ProtocolCraft::Json::Value VexEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    void VexEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char VexEntity::GetDataFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void VexEntity::SetDataFlagsId(const char data_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_flags_id"] = data_flags_id;
    }


    double VexEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double VexEntity::GetHeightImpl() const
    {
        return 0.8;
    }

}
