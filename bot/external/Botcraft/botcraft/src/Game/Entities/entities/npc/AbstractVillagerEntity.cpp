#if PROTOCOL_VERSION > 477 /* > 1.14 */
#include "botcraft/Game/Entities/entities/npc/AbstractVillagerEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractVillagerEntity::metadata_count> AbstractVillagerEntity::metadata_names{ {
        "data_unhappy_counter",
    } };

    AbstractVillagerEntity::AbstractVillagerEntity()
    {
        // Initialize all metadata with default values
        SetDataUnhappyCounter(0);
    }

    AbstractVillagerEntity::~AbstractVillagerEntity()
    {

    }

    bool AbstractVillagerEntity::IsAbstractVillager() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractVillagerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AgeableMobEntity::Serialize();

        output["metadata"]["data_unhappy_counter"] = GetDataUnhappyCounter();

        return output;
    }


    void AbstractVillagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AgeableMobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int AbstractVillagerEntity::GetDataUnhappyCounter() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_unhappy_counter"));
    }


    void AbstractVillagerEntity::SetDataUnhappyCounter(const int data_unhappy_counter)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_unhappy_counter"] = data_unhappy_counter;
    }

}
#endif
