#include "botcraft/Game/Entities/entities/item/FallingBlockEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, FallingBlockEntity::metadata_count> FallingBlockEntity::metadata_names{ {
        "data_start_pos",
    } };

    FallingBlockEntity::FallingBlockEntity()
    {
        // Initialize all metadata with default values
        SetDataStartPos(Position(0, 0, 0));
    }

    FallingBlockEntity::~FallingBlockEntity()
    {

    }


    std::string FallingBlockEntity::GetName() const
    {
        return "falling_block";
    }

    EntityType FallingBlockEntity::GetType() const
    {
        return EntityType::FallingBlockEntity;
    }


    std::string FallingBlockEntity::GetClassName()
    {
        return "falling_block";
    }

    EntityType FallingBlockEntity::GetClassType()
    {
        return EntityType::FallingBlockEntity;
    }


    ProtocolCraft::Json::Value FallingBlockEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_start_pos"] = GetDataStartPos().Serialize();

        return output;
    }


    void FallingBlockEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    Position FallingBlockEntity::GetDataStartPos() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Position>(metadata.at("data_start_pos"));
    }


    void FallingBlockEntity::SetDataStartPos(const Position& data_start_pos)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_start_pos"] = data_start_pos;
    }


    double FallingBlockEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double FallingBlockEntity::GetHeightImpl() const
    {
        return 0.98;
    }

}
