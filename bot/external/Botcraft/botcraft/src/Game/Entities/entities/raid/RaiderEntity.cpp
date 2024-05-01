#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/raid/RaiderEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, RaiderEntity::metadata_count> RaiderEntity::metadata_names{ {
        "is_celebrating",
    } };

    RaiderEntity::RaiderEntity()
    {
        // Initialize all metadata with default values
        SetIsCelebrating(false);
    }

    RaiderEntity::~RaiderEntity()
    {

    }

    bool RaiderEntity::IsRaider() const
    {
        return true;
    }


    ProtocolCraft::Json::Value RaiderEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = PatrollingMonsterEntity::Serialize();

        output["metadata"]["is_celebrating"] = GetIsCelebrating();

        return output;
    }


    void RaiderEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            PatrollingMonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool RaiderEntity::GetIsCelebrating() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("is_celebrating"));
    }


    void RaiderEntity::SetIsCelebrating(const bool is_celebrating)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["is_celebrating"] = is_celebrating;
    }

}
#endif
