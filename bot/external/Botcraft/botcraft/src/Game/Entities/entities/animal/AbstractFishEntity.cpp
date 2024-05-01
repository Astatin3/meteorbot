#include "botcraft/Game/Entities/entities/animal/AbstractFishEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractFishEntity::metadata_count> AbstractFishEntity::metadata_names{ {
        "from_bucket",
    } };

    AbstractFishEntity::AbstractFishEntity()
    {
        // Initialize all metadata with default values
        SetFromBucket(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 3.0) });
    }

    AbstractFishEntity::~AbstractFishEntity()
    {

    }

    bool AbstractFishEntity::IsAbstractFish() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractFishEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = WaterAnimalEntity::Serialize();

        output["metadata"]["from_bucket"] = GetFromBucket();

        return output;
    }


    void AbstractFishEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            WaterAnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool AbstractFishEntity::GetFromBucket() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("from_bucket"));
    }


    void AbstractFishEntity::SetFromBucket(const bool from_bucket)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["from_bucket"] = from_bucket;
    }

}
