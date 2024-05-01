#pragma once

#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundJigsawGeneratePacket : public BaseMessage<ServerboundJigsawGeneratePacket>
    {
    public:
#if   PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x14;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Jigsaw Generate";

        virtual ~ServerboundJigsawGeneratePacket() override
        {

        }
        
        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetLevels(const int levels_)
        {
            levels = levels_;
        }

        void SetKeepJigsaws(const bool keep_jigsaws_)
        {
            keep_jigsaws = keep_jigsaws_;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        int GetLevels() const
        {
            return levels;
        }

        bool GetKeepJigsaws() const
        {
            return keep_jigsaws;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
            levels = ReadData<VarInt>(iter, length);
            keep_jigsaws = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(pos, container);
            WriteData<VarInt>(levels, container);
            WriteData<bool>(keep_jigsaws, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
            output["levels"] = levels;
            output["keep_jigsaws"] = keep_jigsaws;

            return output;
        }

    private:
        NetworkPosition pos;
        int levels = 0;
        bool keep_jigsaws = false;
    };
} //ProtocolCraft
#endif
