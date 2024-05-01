#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/BlockParticle.hpp"

namespace ProtocolCraft
{
    BlockParticle::BlockParticle()
    {
        
    }
    
    BlockParticle::~BlockParticle()
    {
        
    }
    
    std::string BlockParticle::GetName() const
    {
        return "block";
    }
    
    ParticleType BlockParticle::GetType() const
    {
        return ParticleType::Block;
    }

    int BlockParticle::GetState() const
    {
        return state;
    }

    void BlockParticle::SetState(const int state_)
    {
        state = state_;
    }
    
    void BlockParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        state = ReadData<VarInt>(iter, length);
    }
    
    void BlockParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(state, container);
    }
    
    Json::Value BlockParticle::SerializeImpl() const
    {
        Json::Value output;

        output["state"] = state;

        return output;
    }
}
#endif
