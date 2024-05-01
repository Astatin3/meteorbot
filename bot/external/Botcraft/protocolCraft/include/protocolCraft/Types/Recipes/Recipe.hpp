#pragma once

#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class Recipe : public NetworkType
    {
    public:
        virtual ~Recipe() override
        {

        }

        void SetRecipeId(const Identifier& recipe_id_)
        {
            recipe_id = recipe_id_;
        }

        void SetType(const Identifier& type_)
        {
            type = type_;
        }

        void SetData(const std::shared_ptr<RecipeTypeData> data_)
        {
            data = data_;
        }


        const Identifier& GetRecipeId() const
        {
            return recipe_id;
        }
        
        const Identifier& GetType() const
        {
            return type;
        }

        std::shared_ptr<RecipeTypeData> GetData() const
        {
            return data;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 453 /* < 1.14 */
            recipe_id = ReadData<Identifier>(iter, length);
            type = ReadData<Identifier>(iter, length);
#else
            type = ReadData<Identifier>(iter, length);
            recipe_id = ReadData<Identifier>(iter, length);
#endif
            data = RecipeTypeData::CreateRecipeTypeData(type);
            data->Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 453 /* < 1.14 */
            WriteData<Identifier>(recipe_id, container);
            WriteData<Identifier>(type, container);
#else
            WriteData<Identifier>(type, container);
            WriteData<Identifier>(recipe_id, container);
#endif
            data->Write(container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["recipe_id"] = recipe_id;
            output["type"] = type;
            output["data"] = data->Serialize();

            return output;
        }

    private:
        Identifier recipe_id;
        Identifier type;
        std::shared_ptr<RecipeTypeData> data;
    };
}
#endif
