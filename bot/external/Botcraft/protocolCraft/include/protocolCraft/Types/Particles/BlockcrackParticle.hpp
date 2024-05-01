#if PROTOCOL_VERSION < 393 /* < 1.13 */
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class BlockcrackParticle : public Particle
    {
    public:
        BlockcrackParticle();
        
        virtual ~BlockcrackParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;
        
        int GetArgument1() const;
        
        void SetArgument1(const int argument1_);
        
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        
        virtual void WriteImpl(WriteContainer& container) const override;
        
        virtual Json::Value SerializeImpl() const override;
        
    private:
        int argument1 = 0;
        
    };
}
#endif
