#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class TurtleEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 6;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        TurtleEntity();
        virtual ~TurtleEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        Position GetHomePos() const;
        bool GetHasEgg() const;
        bool GetLayingEgg() const;
        Position GetTravelPos() const;
        bool GetGoingHome() const;
        bool GetTravelling() const;

        void SetHomePos(const Position& home_pos);
        void SetHasEgg(const bool has_egg);
        void SetLayingEgg(const bool laying_egg);
        void SetTravelPos(const Position& travel_pos);
        void SetGoingHome(const bool going_home);
        void SetTravelling(const bool travelling);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
