#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#include "protocolCraft/Types/Record.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSectionBlocksUpdatePacket : public BaseMessage<ClientboundSectionBlocksUpdatePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x47;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Section Blocks Update";

        virtual ~ClientboundSectionBlocksUpdatePacket() override
        {

        }

#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
        void SetChunkX(const int chunk_x_)
        {
            chunk_x = chunk_x_;
        }

        void SetChunkZ(const int chunk_z_)
        {
            chunk_z = chunk_z_;
        }

        void SetRecordCount(const int record_count_)
        {
            record_count = record_count_;
        }

        void SetRecords(const std::vector<Record>& records_)
        {
            records = records_;
        }
#else
        void SetSectionPos(const long long int section_pos_)
        {
            section_pos = section_pos_;
        }

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        void SetSuppressLightUpdates(const bool suppress_light_updates_)
        {
            suppress_light_updates = suppress_light_updates_;
        }
#endif

        void SetPositions(const std::vector<short>& positions_)
        {
            positions = positions_;
        }

        void SetStates(const std::vector<int>& states_)
        {
            states = states_;
        }
#endif


#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
        int GetChunkX() const
        {
            return chunk_x;
        }

        int GetChunkZ() const
        {
            return chunk_z;
        }

        int GetRecordCount() const
        {
            return record_count;
        }

        const std::vector<Record>& GetRecords() const
        {
            return records;
        }
#else
        long long int GetSectionPos() const
        {
            return section_pos;
        }

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        bool GetSuppressLightUpdates() const
        {
            return suppress_light_updates;
        }
#endif

        const std::vector<short>& GetPositions() const
        {
            return positions;
        }

        const std::vector<int>& GetStates() const
        {
            return states;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
            chunk_x = ReadData<int>(iter, length);
            chunk_z = ReadData<int>(iter, length);
            record_count = ReadData<VarInt>(iter, length);

            records = std::vector<Record>(record_count);

            for (int i = 0; i < record_count; ++i)
            {
                records[i].Read(iter, length);
            }
#else
            section_pos = ReadData<long long int>(iter, length);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
            suppress_light_updates = ReadData<bool>(iter, length);
#endif
            const int data_size = ReadData<VarInt>(iter, length);
            positions = std::vector<short>(data_size);
            states = std::vector<int>(data_size);
            for (int i = 0; i < data_size; ++i)
            {
                const long long int data = ReadData<VarLong>(iter, length);
                positions[i] = static_cast<short>(data & 0xFFFl);
                states[i] = static_cast<int>(data >> 12);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
            WriteData<int>(chunk_x, container);
            WriteData<int>(chunk_z, container);
            WriteData<VarInt>(record_count, container);
            for (int i = 0; i < record_count; ++i)
            {
                records[i].Write(container);
            }
#else
            WriteData<long long int>(section_pos, container);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
            WriteData<bool>(suppress_light_updates, container);
#endif
            WriteData<VarInt>(static_cast<int>(positions.size()), container);
            for (int i = 0; i < positions.size(); ++i)
            {
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
                WriteData<VarLong>((states[i] << 12) | positions[i], container);
#else
                WriteData<VarLong>((static_cast<long long int>(states[i]) << 12) | static_cast<long long int>(positions[i]), container);
#endif
            }
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
            output["chunk_x"] = chunk_x;
            output["chunk_z"] = chunk_z;
            output["record_count"] = record_count;

            output["records"] = records;
#else
            output["section_pos"] = section_pos;
#if PROTOCOL_VERSION < 763 /* < 1.20 */
            output["suppress_light_updates"] = suppress_light_updates;
#endif
            output["positions"] = positions;
            output["states"] = states;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
        int chunk_x = 0;
        int chunk_z = 0;
        int record_count = 0;
        std::vector<Record> records;
#else
        long long int section_pos = 0;
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        bool suppress_light_updates = false;
#endif
        std::vector<short> positions;
        std::vector<int> states;
#endif
    };
}
