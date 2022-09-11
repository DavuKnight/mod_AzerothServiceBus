/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

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
    class PlayerEventProducer : public PlayerScript
    {

    public:
        RdKafka::Producer* _producer;

        PlayerEventProducer(RdKafka::Producer* producer) : PlayerScript("PlayerEventProducer") {
            _producer = producer;
        }
        ////OnAchiComplete(Player* /*player*/, AchievementEntry const* /*achievement*/) { }
        void OnAchiComplete(Player* player, AchievementEntry const* achievement) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"achievement",boost::json::value_from(achievement)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAchiComplete", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnAchiSave(CharacterDatabaseTransaction /*trans*/, Player* /*player*/, uint16 /*achId*/, CompletedAchievementData /*achiData*/) { }

        ////OnAddToBattleground(Player* /*player*/, Battleground* /*bg*/) { }
        void OnAddToBattleground(Player* player, Battleground* bg) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"battleground",boost::json::value_from(bg)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAddToBattleground", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnAfterGuardianInitStatsForLevel(Player* /*player*/, Guardian* /*guardian*/) { }
        void OnAfterGuardianInitStatsForLevel(Player* player, Guardian* guardian) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"Guardian",boost::json::value_from(guardian)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterGuardianInitStatsForLevel", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnAfterMoveItemFromInventory(Player* /*player*/, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) { }
        void OnAfterMoveItemFromInventory(Player* player, Item* it, uint8 bag, uint8 slot, bool update) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"Item",boost::json::value_from(it) },
                    {"bag",boost::json::value_from(bag) },
                    {"slot",boost::json::value_from(slot) },
                    {"update",boost::json::value_from(update) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnAfterSetVisibleItemSlot(Player* /*player*/, uint8 /*slot*/, Item* /*item*/) { }
        //void OnAfterSetVisibleItemSlot(Player* player, uint8 slot, Item* it) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"Item",boost::json::value_from(it) },
        //            {"slot",boost::json::value_from(slot) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterSetVisibleItemSlot", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnAfterStoreOrEquipNewItem(Player* /*player*/, uint32 /*vendorslot*/, Item* /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/, ItemTemplate const* /*pProto*/, Creature* /*pVendor*/, VendorItem const* /*crItem*/, bool /*bStore*/) { };
        //void OnAfterStoreOrEquipNewItem(Player* player, uint32 vendorslot, Item* item, uint8 count, uint8 bag, uint8 slot,
        //    ItemTemplate const* pProto, Creature* pVendor, VendorItem const* crItem, bool bStore) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"vendorslot",boost::json::value_from(vendorslot) },
        //            {"item",boost::json::value_from(item) },
        //            {"count",boost::json::value_from(count) },
        //            {"bag",boost::json::value_from(bag) },
        //            {"slot",boost::json::value_from(slot) },
        //            {"itemTemplate",boost::json::value_from(pProto) },
        //            {"vendor",boost::json::value_from(pVendor) },
        //            {"vendorItem",boost::json::value_from(crItem) },
        //            {"bStore",boost::json::value_from(bStore) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterStoreOrEquipNewItem", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnAfterUpdateAttackPowerAndDamage(Player* /*player*/, float& /*level*/, float& /*base_attPower*/, float& /*attPowerMod*/, float& /*attPowerMultiplier*/, bool /*ranged*/) { }
        //void OnAfterUpdateAttackPowerAndDamage(Player* player, float& level, float& base_attPower, float& attPowerMod,
        //    float& attPowerMultiplier, bool ranged) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"level",boost::json::value_from(level) },
        //            {"base_attPower",boost::json::value_from(base_attPower) },
        //            {"attPowerMod",boost::json::value_from(attPowerMod) },
        //            {"attPowerMultiplier",boost::json::value_from(attPowerMultiplier) },
        //            {"ranged",boost::json::value_from(ranged) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterUpdateAttackPowerAndDamage", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        ////OnAfterUpdateMaxHealth(Player* /*player*/, float& /*value*/) { }
        //void OnAfterUpdateMaxHealth(Player* player, float& value) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"value",boost::json::value_from(value) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterUpdateMaxHealth", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnAfterUpdateMaxPower(Player* /*player*/, Powers& /*power*/, float& /*value*/) { }
        //void OnAfterUpdateMaxPower(Player* player, Powers& power, float& value) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"power",boost::json::value_from(power) },
        //            {"value",boost::json::value_from(value) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterUpdateMaxPower", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnApplyAmmoBonuses(Player* /*player*/, ItemTemplate const* /*proto*/, float& /*currentAmmoDPS*/) { }
        //void OnApplyAmmoBonuses(Player* player, ItemTemplate const* proto, float& currentAmmoDPS) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"itemTemplate",boost::json::value_from(proto) },
        //            {"currentAmmoDPS",boost::json::value_from(currentAmmoDPS) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnApplyAmmoBonuses", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnBattlegroundDesertion(Player* /*player*/, BattlegroundDesertionType const /*desertionType*/) { }
        void OnBattlegroundDesertion(Player* player, BattlegroundDesertionType const desertionType) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"desertionType",boost::json::value_from(desertionType) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnBattlegroundDesertion", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnBeforeAchiComplete(Player* /*player*/, AchievementEntry const* /*achievement*/) { return true; }
        ////OnBeforeBuyItemFromVendor(Player* /*player*/, ObjectGuid /*vendorguid*/, uint32 /*vendorslot*/, uint32& /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/) { };
        //void OnBeforeBuyItemFromVendor(Player* player, ObjectGuid vendorguid, uint32 vendorslot,
        //    uint32& item, uint8 count, uint8 bag, uint8 slot) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"vendorguid",boost::json::value_from(vendorguid) },
        //            {"vendorslot",boost::json::value_from(vendorslot) },
        //            {"item",boost::json::value_from(item) },
        //            {"count",boost::json::value_from(count) },
        //            {"bag",boost::json::value_from(bag) },
        //            {"slot",boost::json::value_from(slot) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnBeforeBuyItemFromVendor", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        ////OnBeforeChooseGraveyard(Player* /*player*/, TeamId /*teamId*/, bool /*nearCorpse*/, uint32& /*graveyardOverride*/) { }
        //void OnBeforeChooseGraveyard(Player* player, TeamId teamId, bool nearCorpse, uint32& graveyardOverride) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"teamId",boost::json::value_from(teamId) },
        //            {"nearCorpse",boost::json::value_from(nearCorpse) },
        //            {"graveyardOverride",boost::json::value_from(graveyardOverride) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnBeforeBuyItemFromVendor", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnBeforeCriteriaProgress(Player* /*player*/, AchievementCriteriaEntry const* /*criteria*/) { return true; }
        ////OnBeforeDurabilityRepair(Player* /*player*/, ObjectGuid /*npcGUID*/, ObjectGuid /*itemGUID*/, float&/*discountMod*/, uint8 /*guildBank*/) { }
        //void OnBeforeDurabilityRepair(Player* player, ObjectGuid npcGUID, ObjectGuid itemGUID, float& discountMod, uint8 guildBank) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"npcGUID",boost::json::value_from(npcGUID) },
        //            {"itemGUID",boost::json::value_from(itemGUID) },
        //            {"discountMod",boost::json::value_from(discountMod) },
        //            {"guildBank",boost::json::value_from(guildBank) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnBeforeBuyItemFromVendor", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnBeforeGuardianInitStatsForLevel(Player* /*player*/, Guardian* /*guardian*/, CreatureTemplate const* /*cinfo*/, PetType& /*petType*/) { }
        ////OnBeforeInitTalentForLevel(Player* /*player*/, uint8& /*level*/, uint32& /*talentPointsForLevel*/) { }
        ////OnBeforeLoadPetFromDB(Player* /*player*/, uint32& /*petentry*/, uint32& /*petnumber*/, bool& /*current*/, bool& /*forceLoadFromDB*/) { }
        ////OnBeforeSendChatMessage(Player* /*player*/, uint32& /*type*/, uint32& /*lang*/, std::string& /*msg*/) { }
        ////OnBeforeStoreOrEquipNewItem(Player* /*player*/, uint32 /*vendorslot*/, uint32& /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/, ItemTemplate const* /*pProto*/, Creature* /*pVendor*/, VendorItem const* /*crItem*/, bool /*bStore*/) { };
        ////OnBeforeTempSummonInitStats(Player* /*player*/, TempSummon* /*tempSummon*/, uint32& /*duration*/) { }
        ////OnBeforeUpdate(Player* /*player*/, uint32 /*p_time*/) { }
        ////OnBeforeUpdateAttackPowerAndDamage(Player* /*player*/, float& /*level*/, float& /*val2*/, bool /*ranged*/) { }
        ////OnBeingCharmed(Player* /*player*/, Unit* /*charmer*/, uint32 /*oldFactionId*/, uint32 /*newFactionId*/) { }
        ////OnBindToInstance(Player* /*player*/, Difficulty /*difficulty*/, uint32 /*mapId*/, bool /*permanent*/) { }
        ////OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/) { }
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"type",boost::json::value_from(type)},
                    {"lang",boost::json::value_from(lang)},
                    {"msg",boost::json::value_from(msg)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnChat", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Channel* /*channel*/) { }
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"type",boost::json::value_from(type)},
                    {"lang",boost::json::value_from(lang)},
                    {"msg",boost::json::value_from(msg)},
                    {"channel",boost::json::value_from(channel)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnChat", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Group* /*group*/) { }
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"type",boost::json::value_from(type)},
                    {"lang",boost::json::value_from(lang)},
                    {"msg",boost::json::value_from(msg)},
                    {"group",boost::json::value_from(group)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnChat", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        //OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Guild* /*guild*/) { }
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"type",boost::json::value_from(type)},
                    {"lang",boost::json::value_from(lang)},
                    {"msg",boost::json::value_from(msg)},
                    {"guild",boost::json::value_from(guild)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnChat", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        //OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Player* /*receiver*/) { }
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Player* receiver) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"type",boost::json::value_from(type)},
                    {"lang",boost::json::value_from(lang)},
                    {"msg",boost::json::value_from(msg)},
                    {"receiver",boost::json::value_from(receiver)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnChat", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        ////OnCreate(Player* /*player*/) { }
        void OnCreate(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnCreate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        //OnCreateItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) { }
        void OnCreateItem(Player* player, Item* item, uint32 count) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"item",boost::json::value_from(item)},
                    {"count",boost::json::value_from(count)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnCreateItem", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnCreatureKill(Player* /*killer*/, Creature* /*killed*/) { }
        void OnCreatureKill(Player* killer, Creature* killed) override
        {
            try
            {
                boost::json::value jv = {
                    {"killer",boost::json::value_from(killer)},
                    {"killed",boost::json::value_from(killed)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnCreatureKill", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        ////OnCreatureKilledByPet(Player* /*PetOwner*/, Creature* /*killed*/) { }
        void OnCreatureKilledByPet(Player* PetOwner, Creature* killed) override
        {
            try
            {
                boost::json::value jv = {
                    {"PetOwner",boost::json::value_from(PetOwner)},
                    {"killed",boost::json::value_from(killed)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnCreatureKilledByPet", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnCriteriaProgress(Player* /*player*/, AchievementCriteriaEntry const* /*criteria*/) { }
        ////OnCriteriaSave(CharacterDatabaseTransaction /*trans*/, Player* /*player*/, uint16 /*achId*/, CriteriaProgress /*criteriaData*/) { }
        ////OnCustomScalingStatValue(Player* /*player*/, ItemTemplate const* /*proto*/, uint32& /*statType*/, int32& /*val*/, uint8 /*itemProtoStatNumber*/, uint32 /*ScalingStatValue*/, ScalingStatValuesEntry const* /*ssv*/) { }
        ////OnCustomScalingStatValueBefore(Player* /*player*/, ItemTemplate const* /*proto*/, uint8 /*slot*/, bool /*apply*/, uint32& /*CustomScalingStatValue*/) { }
        ////OnDelete(ObjectGuid /*guid*/, uint32 /*accountId*/) { }
        ////OnDeleteFromDB(CharacterDatabaseTransaction /*trans*/, uint32 /*guid*/) { }
        ////OnDuelEnd(Player* /*winner*/, Player* /*loser*/, DuelCompleteType /*type*/) { }
        ////OnDuelRequest(Player* /*target*/, Player* /*challenger*/) { }
        ////OnDuelStart(Player* /*player1*/, Player* /*player2*/) { }
        ////OnEmote(Player* /*player*/, uint32 /*emote*/) { }
        ////OnEquip(Player* /*player*/, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) { }
        ////OnFailedDelete(ObjectGuid /*guid*/, uint32 /*accountId*/) { }
        ////OnFirstLogin(Player* /*player*/) { }
        void OnFirstLogin(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnFirstLogin", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnForgotSpell(Player* /*player*/, uint32 /*spellID*/) {}
        ////OnFreeTalentPointsChanged(Player* /*player*/, uint32 /*points*/) { }
        ////OnGetArenaPersonalRating(Player* /*player*/, uint8 /*slot*/, uint32& /*result*/) { }
        ////OnGetArenaTeamId(Player* /*player*/, uint8 /*slot*/, uint32& /*result*/) { }
        ////OnGetFeralApBonus(Player* /*player*/, int32& /*feral_bonus*/, int32 /*dpsMod*/, ItemTemplate const* /*proto*/, ScalingStatValuesEntry const* /*ssv*/) { }
        ////OnGetMaxPersonalArenaRatingRequirement(Player const* /*player*/, uint32 /*minSlot*/, uint32& /*maxArenaRating*/) const {}
        ////OnGetMaxSkillValue(Player* /*player*/, uint32 /*skill*/, int32& /*result*/, bool /*IsPure*/) { }
        ////OnGetMaxSkillValueForLevel(Player* /*player*/, uint16& /*result*/) { }

        ////OnGetQuestRate(Player* /*player*/, float& /*result*/) { }
        //void OnGetQuestRate(Player* player, float& result) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"questRate",result}
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnGetQuestRate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnGiveXP(Player* /*player*/, uint32& /*amount*/, Unit* /*victim*/) { }
        ////OnGossipSelect(Player* /*player*/, uint32 /*menu_id*/, uint32 /*sender*/, uint32 /*action*/) { }
        void OnGossipSelect(Player* player, uint32 menu_id, uint32 sender, uint32 action) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"menu_id",boost::json::value_from(menu_id)},
                    {"sender",boost::json::value_from(sender)},
                    {"action",boost::json::value_from(action)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnCreatureKilledByPet", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        //////OnGossipSelectCode(Player* /*player*/, uint32 /*menu_id*/, uint32 /*sender*/, uint32 /*action*/, const char* /*code*/) { }
        void OnGossipSelectCode(Player* player, uint32 menu_id, uint32 sender, uint32 action, const char* code) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player)},
                    {"menu_id",boost::json::value_from(menu_id)},
                    {"sender",boost::json::value_from(sender)},
                    {"code",code},
                    {"action",boost::json::value_from(action)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnGossipSelectCode", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnGroupRollRewardItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/, RollVote /*voteType*/, Roll* /*roll*/) { }
        ////OnIsFFAPvP(Player* /*player*/, bool& /*result*/) { }
        //void OnIsFFAPvP(Player* player, bool& result) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"isFFAPvP",result}
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnLearnSpell", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnIsPvP(Player* /*player*/, bool& /*result*/) { }
        //void OnIsPvP(Player* player, bool& result) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"isPvp",result}
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnLearnSpell", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnLearnSpell(Player* /*player*/, uint32 /*spellID*/) {}
        //void OnLearnSpell(Player* player, uint32 spellID) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"player",boost::json::value_from(player) },
        //            {"spellID",spellID}
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnLearnSpell", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnLevelChanged(Player* /*player*/, uint8 /*oldlevel*/) { }
        void OnLevelChanged(Player* player, uint8 oldlevel) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"oldlevel",oldlevel}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnLogin", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        ////OnLoadFromDB(Player* /*player*/) { };

        void OnLogin(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnLogin", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        //OnLogout(Player* /*player*/) { }
        void OnLogout(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnLogout", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        //////OnLootItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/, ObjectGuid /*lootguid*/) { }
        void OnLootItem(Player* player, Item* item, uint32 count, ObjectGuid lootguid) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"item",boost::json::value_from(item) },
                    {"count",boost::json::value_from(count) },
                    {"lootguid",boost::json::value_from(lootguid)}
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnLootItem", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnMapChanged(Player* /*player*/) { }
        void OnMapChanged(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnMapChanged", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnMoneyChanged(Player* /*player*/, int32& /*amount*/) { }
        ////OnPlayerCompleteQuest(Player* /*player*/, Quest const* /*quest_id*/) { }
        void OnPlayerCompleteQuest(Player* player, Quest const* quest_id) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"quest_id",boost::json::value_from(quest_id) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerCompleteQuest", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnPlayerEnterCombat(Player* /*player*/, Unit* /*enemy*/) { }
        void OnPlayerEnterCombat(Player* player, Unit* enemy) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"enemy",boost::json::value_from(enemy) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerCompleteQuest", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnPlayerJoinArena(Player* /*player*/) { }
        void OnPlayerJoinArena(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerJoinArena", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnPlayerJoinBG(Player* /*player*/) { }
        void OnPlayerJoinBG(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerJoinBG", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnPlayerKilledByCreature(Creature* /*killer*/, Player* /*killed*/) { }
        void OnPlayerKilledByCreature(Creature* killer, Player* killed) override
        {
            try
            {
                boost::json::value jv = {
                    {"killer",boost::json::value_from(killer) },
                    {"killed",boost::json::value_from(killed) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerKilledByCreature", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnPlayerLearnTalents(Player* /*player*/, uint32 /*talentId*/, uint32 /*talentRank*/, uint32 /*spellid*/) { }
        ////OnPlayerLeaveCombat(Player* /*player*/) { }
        void OnPlayerLeaveCombat(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerLeaveCombat", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnPlayerPVPFlagChange(Player* /*player*/, bool /*state*/) { }
        ////OnPlayerReleasedGhost(Player* /*player*/) { }
        void OnPlayerReleasedGhost(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerReleasedGhost", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnPlayerResurrect(Player* /*player*/, float /*restore_percent*/, bool /*applySickness*/) { }
        void OnPlayerResurrect(Player* player, float restore_percent, bool applySickness) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"applySickness",boost::json::value_from(applySickness) },
                    {"restore_percent",boost::json::value_from(restore_percent) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPlayerResurrect", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        ////OnPVPKill(Player* /*killer*/, Player* /*killed*/) { }
        void OnPVPKill(Player* killer, Player* killed) override
        {
            try
            {
                boost::json::value jv = {
                    {"killer",boost::json::value_from(killer) },
                    {"killed",boost::json::value_from(killed) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnPVPKill", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnQuestAbandon(Player* /*player*/, uint32 /*questId*/) { }
        void OnQuestAbandon(Player* player, uint32 questId) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"questId",boost::json::value_from(questId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnQuestAbandon", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnQuestComputeXP(Player* /*player*/, Quest const* /*quest*/, uint32& /*xpValue*/) { }
        void OnQuestComputeXP(Player* player, Quest const* quest, uint32& xpValue) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"xpValue",boost::json::value_from(xpValue) },
                    {"quest",boost::json::value_from(quest) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnQuestComputeXP", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnQuestRewardItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) { }
        void OnQuestRewardItem(Player* player, Item* item, uint32 count) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"item",boost::json::value_from(item) },
                    {"count",boost::json::value_from(count) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnQuestComputeXP", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnQueueRandomDungeon(Player* /*player*/, uint32& /*rDungeonId*/) { }
        ////OnRemoveFromBattleground(Player* /*player*/, Battleground* /*bg*/) { }
        ////OnReputationChange(Player* /*player*/, uint32 /*factionID*/, int32& /*standing*/, bool /*incremental*/) { return true; }
        bool OnReputationChange(Player* player, uint32 factionID, int32& standin, bool incremental) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"factionID",boost::json::value_from(factionID) },
                    {"incremental",boost::json::value_from(incremental) },
                    {"standin",boost::json::value_from(standin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnUpdateArea", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
            return true;
        }
        ////OnReputationRankChange(Player* /*player*/, uint32 /*factionID*/, ReputationRank /*newRank*/, ReputationRank /*olRank*/, bool /*increased*/) { }
        ////OnRewardKillRewarder(Player* /*player*/, bool /*isDungeon*/, float& /*rate*/) { }
        ////OnSave(Player* /*player*/) { }
        //void OnSave(Player* player) override
        //{
        //    try
        //    {
        //        boost::json::value jv = boost::json::value_from(player);
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnSave", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnSendInitialPacketsBeforeAddToMap(Player* /*player*/, WorldPacket& /*data*/) {}
        ////OnSetServerSideVisibility(Player* /*player*/, ServerSideVisibilityType& /*type*/, AccountTypes& /*sec*/) { }
        ////OnSetServerSideVisibilityDetect(Player* /*player*/, ServerSideVisibilityType& /*type*/, AccountTypes& /*sec*/) { }
        ////OnSpellCast(Player* /*player*/, Spell* /*spell*/, bool /*skipCheck*/) { }
        ////OnTalentsReset(Player* /*player*/, bool /*noCost*/) { }
        ////OnTextEmote(Player* /*player*/, uint32 /*textEmote*/, uint32 /*emoteNum*/, ObjectGuid /*guid*/) { }
        ////OnUpdate(Player* /*player*/, uint32 /*p_time*/) { }
        ////OnUpdateArea(Player* /*player*/, uint32 /*oldArea*/, uint32 /*newArea*/) { }
        void OnUpdateArea(Player* player, uint32 oldArea, uint32 newArea) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"oldArea",boost::json::value_from(oldArea) },
                    {"newArea",boost::json::value_from(newArea) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnUpdateArea", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        //OnUpdateFaction(Player* /*player*/) { }
        void OnUpdateFaction(Player* player) override
        {
            try
            {
                boost::json::value jv = boost::json::value_from(player);
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnUpdateFaction", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnUpdateZone(Player* /*player*/, uint32 /*newZone*/, uint32 /*newArea*/) { }
        void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"newZone",boost::json::value_from(newZone) },
                    {"newArea",boost::json::value_from(newArea) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnUpdateZone", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        ////OnVictimRewardAfter(Player* /*player*/, Player* /*victim*/, uint32& /*killer_title*/, uint32& /*victim_rank*/, float& /*honor_f*/) { }
        ////OnVictimRewardBefore(Player* /*player*/, Player* /*victim*/, uint32& /*killer_title*/, uint32& /*victim_title*/) { }

    };
}




