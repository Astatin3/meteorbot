#pragma once

#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookUpdatePacket : public BaseMessage<ServerboundRecipeBookUpdatePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x1E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Recipe Book Update";

        virtual ~ServerboundRecipeBookUpdatePacket() override
        {

        }

        void SetPurpose(const int purpose_)
        {
            purpose = purpose_;
        }

#if PROTOCOL_VERSION > 375 /* > 1.12.2 */
        void SetRecipe(const Identifier& recipe_)
#else
        void SetRecipe(const int recipe_)
#endif
        {
            recipe = recipe_;
        }

        void SetGuiOpen(const bool gui_open_)
        {
            gui_open = gui_open_;
        }

        void SetFilteringCraftable(const bool filtering_craftable_)
        {
            filtering_craftable = filtering_craftable_;
        }

#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
        void SetFurnaceGuiOpen(const bool furnace_gui_open_)
        {
            furnace_gui_open = furnace_gui_open_;
        }

        void SetFurnaceFilteringCraftable(const bool furnace_filtering_craftable_)
        {
            furnace_filtering_craftable = furnace_filtering_craftable_;
        }
#endif

#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
        void SetBlastFurnaceGuiOpen(const bool blast_furnace_gui_open_)
        {
            blast_furnace_gui_open = blast_furnace_gui_open_;
        }

        void SetBlastFurnaceFilteringCraftable(const bool blast_furnace_filtering_craftable_)
        {
            blast_furnace_filtering_craftable = blast_furnace_filtering_craftable_;
        }

        void SetSmokerGuiOpen(const bool smoker_gui_open_)
        {
            smoker_gui_open = smoker_gui_open_;
        }

        void SetSmokerFilteringCraftable(const bool smoker_filtering_craftable_)
        {
            smoker_filtering_craftable = smoker_filtering_craftable_;
        }
#endif

        int GetPurpose() const
        {
            return purpose;
        }

#if PROTOCOL_VERSION > 375 /* > 1.12.2 */
        const Identifier& GetRecipe() const
#else
        int GetRecipe() const
#endif
        {
            return recipe;
        }

        bool GetGuiOpen() const
        {
            return gui_open;
        }

        bool GetFilteringCraftable() const
        {
            return filtering_craftable;
        }

#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
        bool GetFurnaceGuiOpen() const
        {
            return furnace_gui_open;
        }

        bool GetFurnaceFilteringCraftable() const
        {
            return furnace_filtering_craftable;
        }
#endif

#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
        bool GetBlastFurnaceGuiOpen() const
        {
            return blast_furnace_gui_open;
        }

        bool GetBlastFurnaceFilteringCraftable() const
        {
            return blast_furnace_filtering_craftable;
        }

        bool GetSmokerGuiOpen() const
        {
            return smoker_gui_open;
        }

        bool GetSmokerFilteringCraftable() const
        {
            return smoker_filtering_craftable;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            purpose = ReadData<VarInt>(iter, length);
            switch (purpose)
            {
            case 0:
#if PROTOCOL_VERSION > 375 /* > 1.12.2 */
                recipe = ReadData<Identifier>(iter, length);
#else
                recipe = ReadData<VarInt>(iter, length);
#endif
                break;
            case 1:
                gui_open = ReadData<bool>(iter, length);
                filtering_craftable = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
                furnace_gui_open = ReadData<bool>(iter, length);
                furnace_filtering_craftable = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
                blast_furnace_gui_open = ReadData<bool>(iter, length);
                blast_furnace_filtering_craftable = ReadData<bool>(iter, length);
                smoker_gui_open = ReadData<bool>(iter, length);
                smoker_filtering_craftable = ReadData<bool>(iter, length);
#endif
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(purpose, container);
            switch (purpose)
            {
            case 0:
#if PROTOCOL_VERSION > 375 /* > 1.12.2 */
                WriteData<Identifier>(recipe, container);
#else
                WriteData<VarInt>(recipe, container);
#endif
                break;
            case 1:
                WriteData<bool>(gui_open, container);
                WriteData<bool>(filtering_craftable, container);
#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
                WriteData<bool>(furnace_gui_open, container);
                WriteData<bool>(furnace_filtering_craftable, container);
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
                WriteData<bool>(blast_furnace_gui_open, container);
                WriteData<bool>(blast_furnace_filtering_craftable, container);
                WriteData<bool>(smoker_gui_open, container);
                WriteData<bool>(smoker_filtering_craftable, container);
#endif
                break;
            default:
                break;
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["purpose"] = purpose;
            switch (purpose)
            {
            case 0:
#if PROTOCOL_VERSION > 375 /* > 1.12.2 */
                output["recipe"] = recipe;
#else
                output["recipe"] = recipe;
#endif
                break;
            case 1:
                output["gui_open"] = gui_open;
                output["filtering_craftable"] = filtering_craftable;
#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
                output["furnace_gui_open"] = furnace_gui_open;
                output["furnace_filtering_craftable"] = furnace_filtering_craftable;
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
                output["blast_furnace_gui_open"] = blast_furnace_gui_open;
                output["blast_furnace_filtering_craftable"] = blast_furnace_filtering_craftable;
                output["smoker_gui_open"] = smoker_gui_open;
                output["smoker_filtering_craftable"] = smoker_filtering_craftable;
#endif
                break;
            default:
                break;
            }

            return output;
        }

    private:
        int purpose = 0;
#if PROTOCOL_VERSION > 375 /* > 1.12.2 */
        Identifier recipe;
#else
        int recipe = 0;
#endif
        bool gui_open = false;
        bool filtering_craftable = false;
#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
        bool furnace_gui_open = false;
        bool furnace_filtering_craftable = false;
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
        bool blast_furnace_gui_open = false;
        bool blast_furnace_filtering_craftable = false;
        bool smoker_gui_open = false;
        bool smoker_filtering_craftable = false;
#endif

    };
} //ProtocolCraft
#endif
