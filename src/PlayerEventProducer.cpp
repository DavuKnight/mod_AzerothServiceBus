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
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

 /*
  * Typical include path in a real application would be
  * #include <librdkafka/rdkafkacpp.h>
  */
#include "../deps/librdkafka-1.8.2/src-cpp/rdkafkacpp.h"
#include <PlayerDto.h>
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
        //OnAchiComplete(Player* /*player*/, AchievementEntry const* /*achievement*/) { }
        //OnAchiSave(CharacterDatabaseTransaction /*trans*/, Player* /*player*/, uint16 /*achId*/, CompletedAchievementData /*achiData*/) { }
        //OnAddToBattleground(Player* /*player*/, Battleground* /*bg*/) { }
        //OnAfterGuardianInitStatsForLevel(Player* /*player*/, Guardian* /*guardian*/) { }
        //OnAfterMoveItemFromInventory(Player* /*player*/, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) { }
        //OnAfterSetVisibleItemSlot(Player* /*player*/, uint8 /*slot*/, Item* /*item*/) { }
        //OnAfterStoreOrEquipNewItem(Player* /*player*/, uint32 /*vendorslot*/, Item* /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/, ItemTemplate const* /*pProto*/, Creature* /*pVendor*/, VendorItem const* /*crItem*/, bool /*bStore*/) { };
        //OnAfterUpdateAttackPowerAndDamage(Player* /*player*/, float& /*level*/, float& /*base_attPower*/, float& /*attPowerMod*/, float& /*attPowerMultiplier*/, bool /*ranged*/) { }
        //OnAfterUpdateMaxHealth(Player* /*player*/, float& /*value*/) { }
        //OnAfterUpdateMaxPower(Player* /*player*/, Powers& /*power*/, float& /*value*/) { }
        //OnApplyAmmoBonuses(Player* /*player*/, ItemTemplate const* /*proto*/, float& /*currentAmmoDPS*/) { }
        //OnBattlegroundDesertion(Player* /*player*/, BattlegroundDesertionType const /*desertionType*/) { }
        //OnBeforeAchiComplete(Player* /*player*/, AchievementEntry const* /*achievement*/) { return true; }
        //OnBeforeBuyItemFromVendor(Player* /*player*/, ObjectGuid /*vendorguid*/, uint32 /*vendorslot*/, uint32& /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/) { };
        //OnBeforeChooseGraveyard(Player* /*player*/, TeamId /*teamId*/, bool /*nearCorpse*/, uint32& /*graveyardOverride*/) { }
        //OnBeforeCriteriaProgress(Player* /*player*/, AchievementCriteriaEntry const* /*criteria*/) { return true; }
        //OnBeforeDurabilityRepair(Player* /*player*/, ObjectGuid /*npcGUID*/, ObjectGuid /*itemGUID*/, float&/*discountMod*/, uint8 /*guildBank*/) { }
        //OnBeforeGuardianInitStatsForLevel(Player* /*player*/, Guardian* /*guardian*/, CreatureTemplate const* /*cinfo*/, PetType& /*petType*/) { }
        //OnBeforeInitTalentForLevel(Player* /*player*/, uint8& /*level*/, uint32& /*talentPointsForLevel*/) { }
        //OnBeforeLoadPetFromDB(Player* /*player*/, uint32& /*petentry*/, uint32& /*petnumber*/, bool& /*current*/, bool& /*forceLoadFromDB*/) { }
        //OnBeforeSendChatMessage(Player* /*player*/, uint32& /*type*/, uint32& /*lang*/, std::string& /*msg*/) { }
        //OnBeforeStoreOrEquipNewItem(Player* /*player*/, uint32 /*vendorslot*/, uint32& /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/, ItemTemplate const* /*pProto*/, Creature* /*pVendor*/, VendorItem const* /*crItem*/, bool /*bStore*/) { };
        //OnBeforeTempSummonInitStats(Player* /*player*/, TempSummon* /*tempSummon*/, uint32& /*duration*/) { }
        //OnBeforeUpdate(Player* /*player*/, uint32 /*p_time*/) { }
        //OnBeforeUpdateAttackPowerAndDamage(Player* /*player*/, float& /*level*/, float& /*val2*/, bool /*ranged*/) { }
        //OnBeingCharmed(Player* /*player*/, Unit* /*charmer*/, uint32 /*oldFactionId*/, uint32 /*newFactionId*/) { }
        //OnBindToInstance(Player* /*player*/, Difficulty /*difficulty*/, uint32 /*mapId*/, bool /*permanent*/) { }
        //OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/) { }
        //OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Channel* /*channel*/) { }
        //OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Group* /*group*/) { }
        //OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Guild* /*guild*/) { }
        //OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Player* /*receiver*/) { }
        //OnCreate(Player* /*player*/) { }
        //OnCreateItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) { }
        //OnCreatureKill(Player* /*killer*/, Creature* /*killed*/) { }
        //OnCreatureKilledByPet(Player* /*PetOwner*/, Creature* /*killed*/) { }
        //OnCriteriaProgress(Player* /*player*/, AchievementCriteriaEntry const* /*criteria*/) { }
        //OnCriteriaSave(CharacterDatabaseTransaction /*trans*/, Player* /*player*/, uint16 /*achId*/, CriteriaProgress /*criteriaData*/) { }
        //OnCustomScalingStatValue(Player* /*player*/, ItemTemplate const* /*proto*/, uint32& /*statType*/, int32& /*val*/, uint8 /*itemProtoStatNumber*/, uint32 /*ScalingStatValue*/, ScalingStatValuesEntry const* /*ssv*/) { }
        //OnCustomScalingStatValueBefore(Player* /*player*/, ItemTemplate const* /*proto*/, uint8 /*slot*/, bool /*apply*/, uint32& /*CustomScalingStatValue*/) { }
        //OnDelete(ObjectGuid /*guid*/, uint32 /*accountId*/) { }
        //OnDeleteFromDB(CharacterDatabaseTransaction /*trans*/, uint32 /*guid*/) { }
        //OnDuelEnd(Player* /*winner*/, Player* /*loser*/, DuelCompleteType /*type*/) { }
        //OnDuelRequest(Player* /*target*/, Player* /*challenger*/) { }
        //OnDuelStart(Player* /*player1*/, Player* /*player2*/) { }
        //OnEmote(Player* /*player*/, uint32 /*emote*/) { }
        //OnEquip(Player* /*player*/, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) { }
        //OnFailedDelete(ObjectGuid /*guid*/, uint32 /*accountId*/) { }
        //OnFirstLogin(Player* /*player*/) { }
        //OnForgotSpell(Player* /*player*/, uint32 /*spellID*/) {}
        //OnFreeTalentPointsChanged(Player* /*player*/, uint32 /*points*/) { }
        //OnGetArenaPersonalRating(Player* /*player*/, uint8 /*slot*/, uint32& /*result*/) { }
        //OnGetArenaTeamId(Player* /*player*/, uint8 /*slot*/, uint32& /*result*/) { }
        //OnGetFeralApBonus(Player* /*player*/, int32& /*feral_bonus*/, int32 /*dpsMod*/, ItemTemplate const* /*proto*/, ScalingStatValuesEntry const* /*ssv*/) { }
        //OnGetMaxPersonalArenaRatingRequirement(Player const* /*player*/, uint32 /*minSlot*/, uint32& /*maxArenaRating*/) const {}
        //OnGetMaxSkillValue(Player* /*player*/, uint32 /*skill*/, int32& /*result*/, bool /*IsPure*/) { }
        //OnGetMaxSkillValueForLevel(Player* /*player*/, uint16& /*result*/) { }
        //OnGetQuestRate(Player* /*player*/, float& /*result*/) { }
        //OnGiveXP(Player* /*player*/, uint32& /*amount*/, Unit* /*victim*/) { }
        //OnGossipSelect(Player* /*player*/, uint32 /*menu_id*/, uint32 /*sender*/, uint32 /*action*/) { }
        //OnGossipSelectCode(Player* /*player*/, uint32 /*menu_id*/, uint32 /*sender*/, uint32 /*action*/, const char* /*code*/) { }
        //OnGroupRollRewardItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/, RollVote /*voteType*/, Roll* /*roll*/) { }
        //OnIsFFAPvP(Player* /*player*/, bool& /*result*/) { }
        //OnIsPvP(Player* /*player*/, bool& /*result*/) { }
        //OnLearnSpell(Player* /*player*/, uint32 /*spellID*/) {}
        //OnLevelChanged(Player* /*player*/, uint8 /*oldlevel*/) { }
        //OnLoadFromDB(Player* /*player*/) { };
        void OnLogin(Player* player) override
        {
            try
            {
                unsigned int flags = boost::archive::no_header;
                SerializeableModels::PlayerDto playerDto = SerializeableModels::PlayerDto::PlayerDto(player);
                std::stringstream stringstream;
                boost::archive::text_oarchive oa(stringstream, flags);
                oa << playerDto;
                std::cout << stringstream.str();
                std::string body = stringstream.str();
                RdKafka::ErrorCode resp = _producer->produce("P.OnLogin", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        //OnLootItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/, ObjectGuid /*lootguid*/) { }
        //OnMapChanged(Player* /*player*/) { }
        //OnMoneyChanged(Player* /*player*/, int32& /*amount*/) { }
        //OnPlayerCompleteQuest(Player* /*player*/, Quest const* /*quest_id*/) { }
        //OnPlayerEnterCombat(Player* /*player*/, Unit* /*enemy*/) { }
        //OnPlayerJoinArena(Player* /*player*/) { }
        //OnPlayerJoinBG(Player* /*player*/) { }
        //OnPlayerKilledByCreature(Creature* /*killer*/, Player* /*killed*/) { }
        //OnPlayerLearnTalents(Player* /*player*/, uint32 /*talentId*/, uint32 /*talentRank*/, uint32 /*spellid*/) { }
        //OnPlayerLeaveCombat(Player* /*player*/) { }
        //OnPlayerPVPFlagChange(Player* /*player*/, bool /*state*/) { }
        //OnPlayerReleasedGhost(Player* /*player*/) { }
        //OnPlayerResurrect(Player* /*player*/, float /*restore_percent*/, bool /*applySickness*/) { }
        //OnPVPKill(Player* /*killer*/, Player* /*killed*/) { }
        //OnQuestAbandon(Player* /*player*/, uint32 /*questId*/) { }
        //OnQuestComputeXP(Player* /*player*/, Quest const* /*quest*/, uint32& /*xpValue*/) { }
        //OnQuestRewardItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) { }
        //OnQueueRandomDungeon(Player* /*player*/, uint32& /*rDungeonId*/) { }
        //OnRemoveFromBattleground(Player* /*player*/, Battleground* /*bg*/) { }
        //OnReputationChange(Player* /*player*/, uint32 /*factionID*/, int32& /*standing*/, bool /*incremental*/) { return true; }
        //OnReputationRankChange(Player* /*player*/, uint32 /*factionID*/, ReputationRank /*newRank*/, ReputationRank /*olRank*/, bool /*increased*/) { }
        //OnRewardKillRewarder(Player* /*player*/, bool /*isDungeon*/, float& /*rate*/) { }
        //OnSave(Player* /*player*/) { }
        //OnSendInitialPacketsBeforeAddToMap(Player* /*player*/, WorldPacket& /*data*/) {}
        //OnSetServerSideVisibility(Player* /*player*/, ServerSideVisibilityType& /*type*/, AccountTypes& /*sec*/) { }
        //OnSetServerSideVisibilityDetect(Player* /*player*/, ServerSideVisibilityType& /*type*/, AccountTypes& /*sec*/) { }
        //OnSpellCast(Player* /*player*/, Spell* /*spell*/, bool /*skipCheck*/) { }
        //OnTalentsReset(Player* /*player*/, bool /*noCost*/) { }
        //OnTextEmote(Player* /*player*/, uint32 /*textEmote*/, uint32 /*emoteNum*/, ObjectGuid /*guid*/) { }
        //OnUpdate(Player* /*player*/, uint32 /*p_time*/) { }
        //OnUpdateArea(Player* /*player*/, uint32 /*oldArea*/, uint32 /*newArea*/) { }
        //OnUpdateFaction(Player* /*player*/) { }
        //OnUpdateZone(Player* /*player*/, uint32 /*newZone*/, uint32 /*newArea*/) { }
        //OnVictimRewardAfter(Player* /*player*/, Player* /*victim*/, uint32& /*killer_title*/, uint32& /*victim_rank*/, float& /*honor_f*/) { }
        //OnVictimRewardBefore(Player* /*player*/, Player* /*victim*/, uint32& /*killer_title*/, uint32& /*victim_title*/) { }

    };
}




