
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
        void OnHeal(Unit* healer, Unit* reciever, uint32& gain) override
        {
            try
            {
                boost::json::value jv = {
                    {"healer",boost::json::value_from(healer) },
                    {"reciever",boost::json::value_from(reciever) },
                    {"gain",boost::json::value_from(gain) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnHeal", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        // Called when a unit deals damage to another unit
        void OnDamage(Unit* attacker, Unit* victim, uint32& damage) override
        {
            try
            {
                boost::json::value jv = {
                    {"attacker",boost::json::value_from(attacker) },
                    {"victim",boost::json::value_from(victim) },
                    {"damage",boost::json::value_from(damage) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnDamage", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        //// Called when DoT's Tick Damage is being Dealt
        //// Attacker can be nullptr if he is despawned while the aura still exists on target
        // void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, uint32& damage) override
        // {
        //     try
        //     {
        //         boost::json::value jv = {
        //             {"target",boost::json::value_from(target) },
        //             {"attacker",boost::json::value_from(attacker) },
        //             {"damage",boost::json::value_from(damage) }
        //         };
        //         std::string body = serialize(jv);

        //         RdKafka::ErrorCode resp = _producer->produce("UnitScript.ModifyPeriodicDamageAurasTick", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //         if (resp != RdKafka::ERR_NO_ERROR) {
        //             std::cerr << "% Produce failed: " <<
        //                 RdKafka::err2str(resp) << std::endl;
        //         }
        //         _producer->poll(0);
        //     }
        //     catch (...)
        //     {
        //     }
        // }


        //// Called when Melee Damage is being Dealt
        // void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage) override
        // {
        //     try
        //     {
        //         boost::json::value jv = {
        //             {"target",boost::json::value_from(target) },
        //             {"attacker",boost::json::value_from(attacker) },
        //             {"damage",boost::json::value_from(damage) }
        //         };
        //         std::string body = serialize(jv);

        //         RdKafka::ErrorCode resp = _producer->produce("UnitScript.ModifyMeleeDamage", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //         if (resp != RdKafka::ERR_NO_ERROR) {
        //             std::cerr << "% Produce failed: " <<
        //                 RdKafka::err2str(resp) << std::endl;
        //         }
        //         _producer->poll(0);
        //     }
        //     catch (...)
        //     {
        //     }
        // }


        //// Called when Spell Damage is being Dealt
        // void ModifySpellDamageTaken(Unit* target, Unit* attacker, int32& damage) override
        // {
        //     try
        //     {
        //         boost::json::value jv = {
        //             {"target",boost::json::value_from(target) },
        //             {"attacker",boost::json::value_from(attacker) },
        //             {"damage",boost::json::value_from(damage) }
        //         };
        //         std::string body = serialize(jv);

        //         RdKafka::ErrorCode resp = _producer->produce("UnitScript.ModifySpellDamageTaken", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //         if (resp != RdKafka::ERR_NO_ERROR) {
        //             std::cerr << "% Produce failed: " <<
        //                 RdKafka::err2str(resp) << std::endl;
        //         }
        //         _producer->poll(0);
        //     }
        //     catch (...)
        //     {
        //     }
        // }


        //// Called when Heal is Recieved
        // void ModifyHealRecieved(Unit* target, Unit* attacker, uint32& damage) override
        // {
        //     try
        //     {
        //         boost::json::value jv = {
        //             {"target",boost::json::value_from(target) },
        //             {"attacker",boost::json::value_from(attacker) },
        //             {"damage",boost::json::value_from(damage) }
        //         };
        //         std::string body = serialize(jv);

        //         RdKafka::ErrorCode resp = _producer->produce("UnitScript.ModifyHealRecieved", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //         if (resp != RdKafka::ERR_NO_ERROR) {
        //             std::cerr << "% Produce failed: " <<
        //                 RdKafka::err2str(resp) << std::endl;
        //         }
        //         _producer->poll(0);
        //     }
        //     catch (...)
        //     {
        //     }
        // }


        //void OnBeforeRollMeleeOutcomeAgainst(Unit const* attacker, Unit const* victim, WeaponAttackType attType, int32& attackerMaxSkillValueForLevel, int32& victimMaxSkillValueForLevel, int32& attackerWeaponSkill, int32& victimDefenseSkill, int32& crit_chance, int32& miss_chance, int32& dodge_chance, int32& parry_chance, int32& block_chance) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"attacker",boost::json::value_from(attacker) },
        //            {"victim",boost::json::value_from(victim) },
        //            {"attType",boost::json::value_from(attType) },
        //            {"attackerMaxSkillValueForLevel",boost::json::value_from(attackerMaxSkillValueForLevel) },
        //            {"victimMaxSkillValueForLevel",boost::json::value_from(victimMaxSkillValueForLevel) },
        //            {"attackerWeaponSkill",boost::json::value_from(attackerWeaponSkill) },
        //            {"victimDefenseSkill",boost::json::value_from(victimDefenseSkill) },
        //            {"crit_chance",boost::json::value_from(crit_chance) },
        //            {"miss_chance",boost::json::value_from(miss_chance) },
        //            {"dodge_chance",boost::json::value_from(dodge_chance) },
        //            {"parry_chance",boost::json::value_from(parry_chance) },
        //            {"block_chance",boost::json::value_from(block_chance) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnBeforeRollMeleeOutcomeAgainst", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //        if (resp != RdKafka::ERR_NO_ERROR) {
        //            std::cerr << "% Produce failed: " <<
        //                RdKafka::err2str(resp) << std::endl;
        //        }
        //        _producer->poll(0);
        //    }
        //    catch (...)
        //    {
        //    }
        //}
        //;

        void OnAuraRemove(Unit* unit, AuraApplication* aurApp, AuraRemoveMode mode) override
        {
            try
            {
                boost::json::value jv = {
                    {"unit",boost::json::value_from(unit) },
                    {"aurApp",boost::json::value_from(aurApp) },
                    {"mode",boost::json::value_from(mode) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnAuraRemove", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        };


        ///**
        // * @brief This hook runs in Unit::Update
        // *
        // * @param unit Contains information about the Unit
        // * @param diff Contains information about the diff time
        // */
        //void OnUnitUpdate(Unit* unit, uint32 diff) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"unit",boost::json::value_from(unit) },
        //            {"diff",boost::json::value_from(diff) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnUnitUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //        if (resp != RdKafka::ERR_NO_ERROR) {
        //            std::cerr << "% Produce failed: " <<
        //                RdKafka::err2str(resp) << std::endl;
        //        }
        //        _producer->poll(0);
        //    }
        //    catch (...)
        //    {
        //    }
        //};


        void OnDisplayIdChange(Unit* unit, uint32 displayId) override
        {
            try
            {
                boost::json::value jv = {
                    {"unit",boost::json::value_from(unit) },
                    {"displayId",boost::json::value_from(displayId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnDisplayIdChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        };


        void OnUnitEnterEvadeMode(Unit* unit, uint8 evadeReason) override
        {
            try
            {
                boost::json::value jv = {
                    {"unit",boost::json::value_from(unit) },
                    {"evadeReason",boost::json::value_from(evadeReason) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnUnitEnterEvadeMode", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        };


        void OnUnitEnterCombat(Unit* unit, Unit* victim) override
        {
            try
            {
                boost::json::value jv = {
                    {"unit",boost::json::value_from(unit) },
                    {"victim",boost::json::value_from(victim) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnUnitEnterCombat", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        };


        void OnUnitDeath(Unit* unit, Unit* killer) override
        {
            try
            {
                boost::json::value jv = {
                    {"unit",boost::json::value_from(unit) },
                    {"killer",boost::json::value_from(killer) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("UnitScript.OnUnitDeath", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        };
    };
}
