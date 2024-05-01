#include "protocolCraft/Types/Particles/Particle.hpp"

#include "protocolCraft/Types/Particles/NoDataTypedParticle.hpp"

#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/BlockParticle.hpp"
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/Types/Particles/BlockMarkerParticle.hpp"
#endif
#include "protocolCraft/Types/Particles/DustParticle.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/DustColorTransitionParticle.hpp"
#endif
#include "protocolCraft/Types/Particles/FallingDustParticle.hpp"
#include "protocolCraft/Types/Particles/ItemParticle.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/Particles/SculkChargeParticle.hpp"
#include "protocolCraft/Types/Particles/ShriekParticle.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/VibrationParticle.hpp"
#endif
#else // 1.12.2
#include "protocolCraft/Types/Particles/IconcrackParticle.hpp"
#include "protocolCraft/Types/Particles/BlockcrackParticle.hpp"
#include "protocolCraft/Types/Particles/BlockdustParticle.hpp"
#include "protocolCraft/Types/Particles/FallingDustParticle.hpp"
#endif

#include <stdexcept>

namespace ProtocolCraft
{
    Particle::Particle()
    {
         
    };

    Particle::~Particle()
    {
         
    };

#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    std::shared_ptr<Particle> Particle::CreateParticle(const ParticleType type)
    {
        switch (type)
        {
        case ParticleType::Block:
            return std::make_shared<BlockParticle>();
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        case ParticleType::BlockMarker:
            return std::make_shared<BlockMarkerParticle>();
#endif
        case ParticleType::Dust:
            return std::make_shared<DustParticle>();
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::DustColorTransition:
            return std::make_shared<DustColorTransitionParticle>();
#endif
        case ParticleType::FallingDust:
            return std::make_shared<FallingDustParticle>();
        case ParticleType::Item:
            return std::make_shared<ItemParticle>();
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case ParticleType::SculkCharge:
            return std::make_shared<SculkChargeParticle>();
        case ParticleType::Shriek:
            return std::make_shared<ShriekParticle>();
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::Vibration:
            return std::make_shared<VibrationParticle>();
#endif
        case ParticleType::AmbientEntityEffect:
        case ParticleType::AngryVillager:
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        case ParticleType::Barrier:
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 757 /* < 1.18 */
        case ParticleType::Light:
#endif
        case ParticleType::Bubble:
        case ParticleType::Cloud:
        case ParticleType::Crit:
        case ParticleType::DamageIndicator:
        case ParticleType::DragonBreath:
        case ParticleType::DrippingLava:
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        case ParticleType::FallingLava:
        case ParticleType::LandingLava:
#endif
        case ParticleType::DrippingWater:
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        case ParticleType::FallingWater:
#endif
        case ParticleType::Effect:
        case ParticleType::ElderGuardian:
        case ParticleType::EnchantedHit:
        case ParticleType::Enchant:
        case ParticleType::EndRod:
        case ParticleType::EntityEffect:
        case ParticleType::ExplosionEmitter:
        case ParticleType::Explosion:
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        case ParticleType::Gust:
        case ParticleType::GustEmitter:
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case ParticleType::SonicBoom:
#endif
        case ParticleType::Firework:
        case ParticleType::Fishing:
        case ParticleType::Flame:
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        case ParticleType::DrippingCherryLeaves:
        case ParticleType::FallingCherryLeaves:
        case ParticleType::LandingCherryLeaves:
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        case ParticleType::CherryLeaves:
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case ParticleType::SculkSoul:
        case ParticleType::SculkChargePop:
#endif
#if PROTOCOL_VERSION > 734 /* > 1.15.2 */
        case ParticleType::SoulFireFlame:
        case ParticleType::Soul:
#endif
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        case ParticleType::Flash:
#endif
        case ParticleType::HappyVillager:
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        case ParticleType::Composter:
#endif
        case ParticleType::Heart:
        case ParticleType::InstantEffect:
        case ParticleType::ItemSlime:
        case ParticleType::ItemSnowball:
        case ParticleType::LargeSmoke:
        case ParticleType::Lava:
        case ParticleType::Mycelium:
        case ParticleType::Note:
        case ParticleType::Poof:
        case ParticleType::Portal:
        case ParticleType::Rain:
        case ParticleType::Smoke:
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        case ParticleType::WhiteSmoke:
#endif
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        case ParticleType::Sneeze:
#endif
        case ParticleType::Spit:
        case ParticleType::SquidInk:
        case ParticleType::SweepAttack:
        case ParticleType::TotemOfUndying:
        case ParticleType::Underwater:
        case ParticleType::Splash:
        case ParticleType::Witch:
        case ParticleType::BubblePop:
        case ParticleType::CurrentDown:
        case ParticleType::BubbleColumnUp:
        case ParticleType::Nautilus:
        case ParticleType::Dolphin:
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        case ParticleType::CampfireCosySmoke:
        case ParticleType::CampfireSignalSmoke:
#endif
#if PROTOCOL_VERSION > 572 /* > 1.14.4 */
        case ParticleType::DrippingHoney:
        case ParticleType::FallingHoney:
        case ParticleType::LandingHoney:
        case ParticleType::FallingNectar:
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::FallingSporeBlossom:
#endif
#if PROTOCOL_VERSION > 734 /* > 1.15.2 */
        case ParticleType::Ash:
        case ParticleType::CrimsonSpore:
        case ParticleType::WarpedSpore:
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::SporeBlossomAir:
#endif
#if PROTOCOL_VERSION > 734 /* > 1.15.2 */
        case ParticleType::DrippingObsidianTear:
        case ParticleType::FallingObsidianTear:
        case ParticleType::LandingObsidianTear:
        case ParticleType::ReversePortal:
        case ParticleType::WhiteAsh:
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::SmallFlame:
        case ParticleType::Snowflake:
        case ParticleType::DrippingDripstoneLava:
        case ParticleType::FallingDripstoneLava:
        case ParticleType::DrippingDripstoneWater:
        case ParticleType::FallingDripstoneWater:
        case ParticleType::GlowSquidInk:
        case ParticleType::Glow:
        case ParticleType::WaxOn:
        case ParticleType::WaxOff:
        case ParticleType::ElectricSpark:
        case ParticleType::Scrape:
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        case ParticleType::EggCrack:
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        case ParticleType::DustPlume:
        case ParticleType::GustDust:
        case ParticleType::TrialSpawnerDetection:
#endif
            return std::make_shared<NoDataTypedParticle>(type);
        default:
            throw std::runtime_error("Unable to create particle with id: " + std::to_string(static_cast<int>(type)) + ".");
        }
    }
#else //1.12.2
    std::shared_ptr<Particle> Particle::CreateParticle(const ParticleType type)
    {
        switch (type)
        {
        case ParticleType::Iconcrack:
            return std::make_shared<IconcrackParticle>();
        case ParticleType::Blockcrack:
            return std::make_shared<BlockcrackParticle>();
        case ParticleType::Blockdust:
            return std::make_shared<BlockdustParticle>();
        case ParticleType::FallingDust:
            return std::make_shared<FallingDustParticle>();
        case ParticleType::Explode:
        case ParticleType::LargeExplode:
        case ParticleType::HugeExplosion:
        case ParticleType::FireworksSpark:
        case ParticleType::Bubble:
        case ParticleType::Splash:
        case ParticleType::Wake:
        case ParticleType::Suspended:
        case ParticleType::Depthsuspend:
        case ParticleType::Crit:
        case ParticleType::MagicCrit:
        case ParticleType::Smoke:
        case ParticleType::LargeSmoke:
        case ParticleType::Spell:
        case ParticleType::InstantSpell:
        case ParticleType::MobSpell:
        case ParticleType::MobSpellAmbient:
        case ParticleType::WitchMagic:
        case ParticleType::DripWater:
        case ParticleType::DripLava:
        case ParticleType::AngryVillager:
        case ParticleType::HappyVillager:
        case ParticleType::Townaura:
        case ParticleType::Note:
        case ParticleType::Portal:
        case ParticleType::EnchantmentTable:
        case ParticleType::Flame:
        case ParticleType::Lava:
        case ParticleType::Footstep:
        case ParticleType::Cloud:
        case ParticleType::Reddust:
        case ParticleType::Snowballpoof:
        case ParticleType::Snowshovel:
        case ParticleType::Slime:
        case ParticleType::Heart:
        case ParticleType::Barrier:
        case ParticleType::Droplet:
        case ParticleType::Take:
        case ParticleType::MobAppearance:
        case ParticleType::DragonBreath:
        case ParticleType::EndRod:
        case ParticleType::DamageIndicator:
        case ParticleType::SweepAttack:
        case ParticleType::Totem:
        case ParticleType::Spit:
            return std::make_shared<NoDataTypedParticle>(type);
        default:
            throw std::runtime_error("Unable to create particle with id: " + std::to_string(static_cast<int>(type)) + ".");
        }
    }
#endif
}
