
#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>
#include <sstream>

#if _AIX
#include <unistd.h>
#endif
#include <boost/json.hpp>
#include <rdkafkacpp.h>
#include <boost/json/value_from.hpp>
#include <boost/json/value.hpp> // prevent intellisense bugs
#include "Serialization/Templates.h"
// Add player scripts
namespace mod_AzerothServiceBus
{
    class UnitEventProducer : public UnitScript
    {

    public:
        RdKafka::Producer* _producer;

        UnitEventProducer(RdKafka::Producer* producer) : UnitScript("PlayerEventProducer") {
            _producer = producer;
        }
        // Called when a unit deals healing to another unit
        void OnHeal(Unit* healer, Unit* reciever, uint32& gain) override { }

        // Called when a unit deals damage to another unit
        void OnDamage(Unit* attacker, Unit* victim, uint32& damage) override { }

        // Called when DoT's Tick Damage is being Dealt
        // Attacker can be nullptr if he is despawned while the aura still exists on target
         void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, uint32& damage) override { }

        // Called when Melee Damage is being Dealt
         void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage) override { }

        // Called when Spell Damage is being Dealt
         void ModifySpellDamageTaken(Unit* target, Unit* attacker, int32& damage) override { }

        // Called when Heal is Recieved
         void ModifyHealRecieved(Unit* target, Unit* attacker, uint32& damage) override { }

        //Called when Damage is Dealt
         uint32 DealDamage(Unit* AttackerUnit, Unit* pVictim, uint32 damage, DamageEffectType damagetype) override { return damage; }

         void OnBeforeRollMeleeOutcomeAgainst(Unit const* attacker, Unit const* victim, WeaponAttackType attType, int32& attackerMaxSkillValueForLevel, int32& victimMaxSkillValueForLevel, int32& attackerWeaponSkill, int32& victimDefenseSkill, int32& crit_chance, int32& miss_chance, int32& dodge_chance, int32& parry_chance, int32& block_chance) override {   };

         void OnAuraRemove(Unit* unit, AuraApplication* aurApp, AuraRemoveMode mode) override { }

        bool IfNormalReaction(Unit const* unit, Unit const* target, ReputationRank& repRank) override { return true; }

        bool IsNeedModSpellDamagePercent(Unit const* unit, AuraEffect* auraEff, float& doneTotalMod, SpellInfo const* spellProto) override { return true; }

        bool IsNeedModMeleeDamagePercent(Unit const* unit, AuraEffect* auraEff, float& doneTotalMod, SpellInfo const* spellProto) override { return true; }

        bool IsNeedModHealPercent(Unit const* unit, AuraEffect* auraEff, float& doneTotalMod, SpellInfo const* spellProto)override { return true; }

        bool CanSetPhaseMask(Unit const* unit, uint32 newPhaseMask, bool update) override { return true; }

        bool IsCustomBuildValuesUpdate(Unit const* unit, uint8 updateType, ByteBuffer& fieldBuffer, Player const* target, uint16 index) override { return false; }

        bool OnBuildValuesUpdate(Unit const* unit, uint8 updateType, ByteBuffer& fieldBuffer, Player* target, uint16 index) override { return false; }

        /**
         * @brief This hook runs in Unit::Update
         *
         * @param unit Contains information about the Unit
         * @param diff Contains information about the diff time
         */
        void OnUnitUpdate(Unit* unit, uint32 diff) override { }

        void OnDisplayIdChange(Unit* unit, uint32 displayId) override { }

        void OnUnitEnterEvadeMode(Unit* unit, uint8 evadeReason) override { }

        void OnUnitEnterCombat(Unit* unit, Unit* victim) override { }

        void OnUnitDeath(Unit* unit, Unit* killer) override{ }


    };
}
