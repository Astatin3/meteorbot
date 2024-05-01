#include "botcraft/Game/Entities/entities/monster/SkeletonEntity.hpp"

#include <mutex>

namespace Botcraft
{
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    const std::array<std::string, SkeletonEntity::metadata_count> SkeletonEntity::metadata_names{ {
        "data_stray_conversion_id",
    } };
#endif

    SkeletonEntity::SkeletonEntity()
    {
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        // Initialize all metadata with default values
        SetDataStrayConversionId(false);
#endif
    }

    SkeletonEntity::~SkeletonEntity()
    {

    }


    std::string SkeletonEntity::GetName() const
    {
        return "skeleton";
    }

    EntityType SkeletonEntity::GetType() const
    {
        return EntityType::Skeleton;
    }


    std::string SkeletonEntity::GetClassName()
    {
        return "skeleton";
    }

    EntityType SkeletonEntity::GetClassType()
    {
        return EntityType::Skeleton;
    }


#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    ProtocolCraft::Json::Value SkeletonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractSkeletonEntity::Serialize();

        output["metadata"]["data_stray_conversion_id"] = GetDataStrayConversionId();

        return output;
    }


    void SkeletonEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractSkeletonEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool SkeletonEntity::GetDataStrayConversionId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_stray_conversion_id"));
    }


    void SkeletonEntity::SetDataStrayConversionId(const bool data_stray_conversion_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_stray_conversion_id"] = data_stray_conversion_id;
    }
#endif


    double SkeletonEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double SkeletonEntity::GetHeightImpl() const
    {
        return 1.99;
    }

}
