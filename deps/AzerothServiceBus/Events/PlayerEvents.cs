using AzerothServiceBus.Models;
using Confluent.Kafka;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AzerothServiceBus
{
    public static class PlayerEvents
    {
        static IProducer<Null, MarchelledPlayer> nullBuilder;
        static PlayerEvents()
        {
            try
            {
                var config = new ProducerConfig
                {
                    BootstrapServers = "localhost:9092"
                };
                nullBuilder = new ProducerBuilder<Null, MarchelledPlayer>(config).Build();
            }
            catch (Exception exc)
            {
                Console.WriteLine(exc.Message);
            }
        }

        private static void sendPlayerEvent(string eventName, MarchelledPlayer player)
        {
            Console.WriteLine(eventName);
            nullBuilder.Produce(eventName, new Message<Null, MarchelledPlayer> { Value = player });
        }

        //virtual void OnPlayerReleasedGhost(Player* /*player*/) { }
        public static int OnPlayerReleasedGhost(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnPlayerReleasedGhost", player);
            return 0;
        }
        // Called on Send Initial Packets Before Add To Map
        //virtual void OnSendInitialPacketsBeforeAddToMap(Player* /*player*/, WorldPacket& /*data*/) { }
        public static void OnSendInitialPacketsBeforeAddToMap(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnSendInitialPacketsBeforeAddToMap", player);
            return;
        }

        // Called when a player does a desertion action (see BattlegroundDesertionType)
        //virtual void OnBattlegroundDesertion(Player* /*player*/, BattlegroundDesertionType const /*desertionType*/) { }
        public static void OnBattlegroundDesertion(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnBattlegroundDesertion", player);
            return;
        }

        // Called when a player completes a quest
        //virtual void OnPlayerCompleteQuest(Player* /*player*/, Quest const* /*quest_id*/) { }
        public static void OnPlayerCompleteQuest(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnPlayerCompleteQuest", player);
            return;
        }
        // Called when a player kills another player
        //virtual void OnPVPKill(Player* /*killer*/, Player* /*killed*/) { }
        public static void OnPVPKill(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnPVPKill", player);
            return;
        }
        // Called when a player toggles pvp
        //virtual void OnPlayerPVPFlagChange(Player* /*player*/, bool /*state*/) { }
        public static void OnPlayerPVPFlagChange(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnPlayerPVPFlagChange", player);
            return;
        }
        // Called when a player kills a creature
        //virtual void OnCreatureKill(Player* /*killer*/, Creature* /*killed*/) { }
        public static void OnCreatureKill(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnCreatureKill", player);
            return;
        }
        // Called when a player's pet kills a creature
        //virtual void OnCreatureKilledByPet(Player* /*PetOwner*/, Creature* /*killed*/) { }
        public static void OnCreatureKilledByPet(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnCreatureKilledByPet", player);
            return;
        }
        // Called when a player is killed by a creature
        //virtual void OnPlayerKilledByCreature(Creature* /*killer*/, Player* /*killed*/) { }
        public static void OnPlayerKilledByCreature(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnPlayerKilledByCreature", player);
            return;
        }
        // Called when a player's level changes (right after the level is applied)
        //virtual void OnLevelChanged(Player* /*player*/, uint8 /*oldlevel*/) { }
        public static void OnLevelChanged(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnLevelChanged", player);
            return;
        }
        // Called when a player's free talent points change (right before the change is applied)
        //virtual void OnFreeTalentPointsChanged(Player* /*player*/, uint32 /*points*/) { }
        public static void OnFreeTalentPointsChanged(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnFreeTalentPointsChanged", player);
            return;
        }
        // Called when a player's talent points are reset (right before the reset is done)
        //virtual void OnTalentsReset(Player* /*player*/, bool /*noCost*/) { }
        public static void OnTalentsReset(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            sendPlayerEvent("OnTalentsReset", player);
            return;
        }
        // Called for player::update
        //virtual void OnBeforeUpdate(Player* /*player*/, uint32 /*p_time*/) { }
        public static void OnBeforeUpdate(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            //sendPlayerEvent("OnUpdate", player);
            return;
        }
        //virtual void OnUpdate(Player* /*player*/, uint32 /*p_time*/) { }
        public static void OnUpdate(IntPtr arg, int argLength)
        {
            var player = new MarchelledPlayer(arg);
            //sendPlayerEvent("OnUpdate", player);
            return;
        }
        // Called when a player's money is modified (before the modification is done)
        //virtual void OnMoneyChanged(Player* /*player*/, int32& /*amount*/) { }

        // Called when a player gains XP (before anything is given)
        //virtual void OnGiveXP(Player* /*player*/, uint32& /*amount*/, Unit* /*victim*/) { }

        // Called when a player's reputation changes (before it is actually changed)
        //virtual bool OnReputationChange(Player* /*player*/, uint32 /*factionID*/, int32& /*standing*/, bool /*incremental*/) { return true; }

        // Called when a player's reputation rank changes (before it is actually changed)
        //virtual void OnReputationRankChange(Player* /*player*/, uint32 /*factionID*/, ReputationRank /*newRank*/, ReputationRank /*olRank*/, bool /*increased*/) { }

        // Called when a player learned new spell
        //virtual void OnLearnSpell(Player* /*player*/, uint32 /*spellID*/) { }

        // Called when a player forgot spell
        //virtual void OnForgotSpell(Player* /*player*/, uint32 /*spellID*/) { }

        // Called when a duel is requested
        //virtual void OnDuelRequest(Player* /*target*/, Player* /*challenger*/) { }

        // Called when a duel starts (after 3s countdown)
        //virtual void OnDuelStart(Player* /*player1*/, Player* /*player2*/) { }

        // Called when a duel ends
        //virtual void OnDuelEnd(Player* /*winner*/, Player* /*loser*/, DuelCompleteType /*type*/) { }

        // The following methods are called when a player sends a chat message.
        //virtual void OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/) { }

        //virtual void OnBeforeSendChatMessage(Player* /*player*/, uint32& /*type*/, uint32& /*lang*/, std::string& /*msg*/) { }

        //virtual void OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Player* /*receiver*/) { }

        //virtual void OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Group* /*group*/) { }

        //virtual void OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Guild* /*guild*/) { }

        //virtual void OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Channel* /*channel*/) { }

        // Both of the below are called on emote opcodes.
        //virtual void OnTextEmote(Player* /*player*/, uint32 /*emote*/) { }

        //virtual void OnTextEmote(Player* /*player*/, uint32 /*textEmote*/, uint32 /*emoteNum*/, ObjectGuid /*guid*/) { }

        // Called in Spell::Cast.
        //virtual void OnSpellCast(Player* /*player*/, Spell* /*spell*/, bool /*skipCheck*/) { }

        // Called during data loading
        //virtual void OnLoadFromDB(Player* /*player*/) { };

        // Called when a player logs in.
        //virtual void OnLogin(Player* /*player*/) { }
        public static void OnLogin(IntPtr arg, int argLength) { var player = new MarchelledPlayer(arg); sendPlayerEvent("OnLogin", player); return; }

        // Called when a player logs out.
        //virtual void OnLogout(Player* /*player*/) { }

        // Called when a player is created.
        //virtual void OnCreate(Player* /*player*/) { }

        // Called when a player is deleted.
        //virtual void OnDelete(ObjectGuid /*guid*/, uint32 /*accountId*/) { }

        // Called when a player delete failed.
        //virtual void OnFailedDelete(ObjectGuid /*guid*/, uint32 /*accountId*/) { }

        // Called when a player is about to be saved.
        //virtual void OnSave(Player* /*player*/) { }

        // Called when a player is bound to an instance
        //virtual void OnBindToInstance(Player* /*player*/, Difficulty /*difficulty*/, uint32 /*mapId*/, bool /*permanent*/) { }

        // Called when a player switches to a new zone
        //virtual void OnUpdateZone(Player* /*player*/, uint32 /*newZone*/, uint32 /*newArea*/) { }

        // Called when a player switches to a new area (more accurate than UpdateZone)
        //virtual void OnUpdateArea(Player* /*player*/, uint32 /*oldArea*/, uint32 /*newArea*/) { }

        // Called when a player changes to a new map (after moving to new map)
        //virtual void OnMapChanged(Player* /*player*/) { }

        // Called before a player is being teleported to new coords
        //[[nodiscard]] virtual bool OnBeforeTeleport(Player* /*player*/, uint32 /*mapid*/, float /*x*/, float /*y*/, float /*z*/, float /*orientation*/, uint32 /*options*/, Unit* /*target*/) { return true; }

        // Called when team/faction is set on player
        //virtual void OnUpdateFaction(Player* /*player*/) { }

        // Called when a player is added to battleground
        //virtual void OnAddToBattleground(Player* /*player*/, Battleground* /*bg*/) { }

        // Called when a player queues a Random Dungeon using the RDF (Random Dungeon Finder)
        //virtual void OnQueueRandomDungeon(Player* /*player*/, uint32 & /*rDungeonId*/) { }

        // Called when a player is removed from battleground
        //virtual void OnRemoveFromBattleground(Player* /*player*/, Battleground* /*bg*/) { }

        // Called when a player complete an achievement
        //virtual void OnAchiComplete(Player* /*player*/, AchievementEntry const* /*achievement*/) { }

        // Called before player complete an achievement, can be used to disable achievements in certain conditions
        //virtual bool OnBeforeAchiComplete(Player* /*player*/, AchievementEntry const* /*achievement*/) { return true; }

        // Called when a player complete an achievement criteria
        //virtual void OnCriteriaProgress(Player* /*player*/, AchievementCriteriaEntry const* /*criteria*/) { }

        //  Called before player complete an achievement criteria, can be used to disable achievement criteria in certain conditions
        //virtual bool OnBeforeCriteriaProgress(Player* /*player*/, AchievementCriteriaEntry const* /*criteria*/) { return true; }

        // Called when an Achievement is saved to DB
        //virtual void OnAchiSave(CharacterDatabaseTransaction /*trans*/, Player* /*player*/, uint16 /*achId*/, CompletedAchievementData /*achiData*/) { }

        // Called when an Criteria is saved to DB
        //virtual void OnCriteriaSave(CharacterDatabaseTransaction /*trans*/, Player* /*player*/, uint16 /*achId*/, CriteriaProgress /*criteriaData*/) { }

        // Called when a player selects an option in a player gossip window
        //virtual void OnGossipSelect(Player* /*player*/, uint32 /*menu_id*/, uint32 /*sender*/, uint32 /*action*/) { }

        // Called when a player selects an option in a player gossip window
        //virtual void OnGossipSelectCode(Player* /*player*/, uint32 /*menu_id*/, uint32 /*sender*/, uint32 /*action*/, const char* /*code*/) { }

        // On player getting charmed
        //virtual void OnBeingCharmed(Player* /*player*/, Unit* /*charmer*/, uint32 /*oldFactionId*/, uint32 /*newFactionId*/) { }

        // To change behaviour of set visible item slot
        //virtual void OnAfterSetVisibleItemSlot(Player* /*player*/, uint8 /*slot*/, Item* /*item*/) { }

        // After an item has been moved from inventory
        //virtual void OnAfterMoveItemFromInventory(Player* /*player*/, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) { }

        // After an item has been equipped
        //virtual void OnEquip(Player* /*player*/, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) { }

        // After player enters queue for BG
        //virtual void OnPlayerJoinBG(Player* /*player*/) { }

        // After player enters queue for Arena
        //virtual void OnPlayerJoinArena(Player* /*player*/) { }

        //Called when trying to get a team ID of a slot > 2 (This is for custom teams created by modules)
        //virtual void GetCustomGetArenaTeamId(Player const* /*player*/, uint8 /*slot*/, uint32& /*teamID*/) const { }

        //Called when trying to get players personal rating of an arena slot > 2 (This is for custom teams created by modules)
        //virtual void GetCustomArenaPersonalRating(Player const* /*player*/, uint8 /*slot*/, uint32& /*rating*/) const { }

        //Called after the normal slots (0..2) for arena have been evaluated so that custom arena teams could modify it if nececasry
        //virtual void OnGetMaxPersonalArenaRatingRequirement(Player const* /*player*/, uint32 /*minSlot*/, uint32& /*maxArenaRating*/) const {}

        //After looting item
        //virtual void OnLootItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/, ObjectGuid /*lootguid*/) { }

        //After creating item (eg profession item creation)
        //virtual void OnCreateItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) { }

        // After receiving item as a quest reward
        //virtual void OnQuestRewardItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) { }

        // After receiving item as a group roll reward
        //virtual void OnGroupRollRewardItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/, RollVote /*voteType*/, Roll* /*roll*/) { }

        // After completed a quest
        //[[nodiscard]] virtual bool OnBeforeQuestComplete(Player* /*player*/, uint32 /*quest_id*/) { return true; }

        // Called after computing the XP reward value for a quest
        //virtual void OnQuestComputeXP(Player* /*player*/, Quest const* /*quest*/, uint32& /*xpValue*/) { }

        // Before durability repair action, you can even modify the discount value
        //virtual void OnBeforeDurabilityRepair(Player* /*player*/, ObjectGuid /*npcGUID*/, ObjectGuid /*itemGUID*/, float&/*discountMod*/, uint8 /*guildBank*/) { }

        //Before buying something from any vendor
        //virtual void OnBeforeBuyItemFromVendor(Player* /*player*/, ObjectGuid /*vendorguid*/, uint32 /*vendorslot*/, uint32& /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/) { };

        //Before buying something from any vendor
        //virtual void OnBeforeStoreOrEquipNewItem(Player* /*player*/, uint32 /*vendorslot*/, uint32& /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/, ItemTemplate const* /*pProto*/, Creature* /*pVendor*/, VendorItem const* /*crItem*/, bool /*bStore*/) { };

        //After buying something from any vendor
        //virtual void OnAfterStoreOrEquipNewItem(Player* /*player*/, uint32 /*vendorslot*/, Item* /*item*/, uint8 /*count*/, uint8 /*bag*/, uint8 /*slot*/, ItemTemplate const* /*pProto*/, Creature* /*pVendor*/, VendorItem const* /*crItem*/, bool /*bStore*/) { };

        //virtual void OnAfterUpdateMaxPower(Player* /*player*/, Powers& /*power*/, float& /*value*/) { }

        //virtual void OnAfterUpdateMaxHealth(Player* /*player*/, float& /*value*/) { }

        //virtual void OnBeforeUpdateAttackPowerAndDamage(Player* /*player*/, float& /*level*/, float& /*val2*/, bool /*ranged*/) { }
        //virtual void OnAfterUpdateAttackPowerAndDamage(Player* /*player*/, float& /*level*/, float& /*base_attPower*/, float& /*attPowerMod*/, float& /*attPowerMultiplier*/, bool /*ranged*/) { }

        //virtual void OnBeforeInitTalentForLevel(Player* /*player*/, uint8& /*level*/, uint32& /*talentPointsForLevel*/) { }

        //virtual void OnFirstLogin(Player* /*player*/) { }

        //[[nodiscard]] virtual bool CanJoinInBattlegroundQueue(Player* /*player*/, ObjectGuid /*BattlemasterGuid*/, BattlegroundTypeId /*BGTypeID*/, uint8 /*joinAsGroup*/, GroupJoinBattlegroundResult& /*err*/) { return true; }
        //virtual bool ShouldBeRewardedWithMoneyInsteadOfExp(Player* /*player*/) { return false; }

        // Called before the player's temporary summoned creature has initialized it's stats
        //virtual void OnBeforeTempSummonInitStats(Player* /*player*/, TempSummon* /*tempSummon*/, uint32& /*duration*/) { }

        // Called before the player's guardian / pet has initialized it's stats for the player's level
        //virtual void OnBeforeGuardianInitStatsForLevel(Player* /*player*/, Guardian* /*guardian*/, CreatureTemplate const* /*cinfo*/, PetType& /*petType*/) { }

        // Called after the player's guardian / pet has initialized it's stats for the player's level
        //virtual void OnAfterGuardianInitStatsForLevel(Player* /*player*/, Guardian* /*guardian*/) { }

        // Called before loading a player's pet from the DB
        //virtual void OnBeforeLoadPetFromDB(Player* /*player*/, uint32& /*petentry*/, uint32& /*petnumber*/, bool& /*current*/, bool& /*forceLoadFromDB*/) { }

        //[[nodiscard]] virtual bool CanJoinInArenaQueue(Player* /*player*/, ObjectGuid /*BattlemasterGuid*/, uint8 /*arenaslot*/, BattlegroundTypeId /*BGTypeID*/, uint8 /*joinAsGroup*/, uint8 /*IsRated*/, GroupJoinBattlegroundResult& /*err*/) { return true; }

        //[[nodiscard]] virtual bool CanBattleFieldPort(Player* /*player*/, uint8 /*arenaType*/, BattlegroundTypeId /*BGTypeID*/, uint8 /*action*/) { return true; }

        //[[nodiscard]] virtual bool CanGroupInvite(Player* /*player*/, std::string& /*membername*/) { return true; }

        //[[nodiscard]] virtual bool CanGroupAccept(Player* /*player*/, Group* /*group*/) { return true; }

        //[[nodiscard]] virtual bool CanSellItem(Player* /*player*/, Item* /*item*/, Creature* /*creature*/) { return true; }

        //[[nodiscard]] virtual bool CanSendMail(Player* /*player*/, ObjectGuid /*receiverGuid*/, ObjectGuid /*mailbox*/, std::string& /*subject*/, std::string& /*body*/, uint32 /*money*/, uint32 /*COD*/, Item* /*item*/) { return true; }

        //virtual void PetitionBuy(Player* /*player*/, Creature* /*creature*/, uint32& /*charterid*/, uint32& /*cost*/, uint32& /*type*/) { }

        //virtual void PetitionShowList(Player* /*player*/, Creature* /*creature*/, uint32& /*CharterEntry*/, uint32& /*CharterDispayID*/, uint32& /*CharterCost*/) { }

        //virtual void OnRewardKillRewarder(Player* /*player*/, bool /*isDungeon*/, float& /*rate*/) { }

        //[[nodiscard]] virtual bool CanGiveMailRewardAtGiveLevel(Player* /*player*/, uint8 /*level*/) { return true; }

        //virtual void OnDeleteFromDB(CharacterDatabaseTransaction /*trans*/, uint32 /*guid*/) { }

        //[[nodiscard]] virtual bool CanRepopAtGraveyard(Player* /*player*/) { return true; }

        //virtual void OnGetMaxSkillValue(Player* /*player*/, uint32 /*skill*/, int32& /*result*/, bool /*IsPure*/) { }

        //[[nodiscard]] virtual bool CanAreaExploreAndOutdoor(Player* /*player*/) { return true; }

        //virtual void OnVictimRewardBefore(Player* /*player*/, Player* /*victim*/, uint32& /*killer_title*/, uint32& /*victim_title*/) { }

        //virtual void OnVictimRewardAfter(Player* /*player*/, Player* /*victim*/, uint32& /*killer_title*/, uint32& /*victim_rank*/, float& /*honor_f*/) { }

        //virtual void OnCustomScalingStatValueBefore(Player* /*player*/, ItemTemplate const* /*proto*/, uint8 /*slot*/, bool /*apply*/, uint32& /*CustomScalingStatValue*/) { }

        //virtual void OnCustomScalingStatValue(Player* /*player*/, ItemTemplate const* /*proto*/, uint32& /*statType*/, int32& /*val*/, uint8 /*itemProtoStatNumber*/, uint32 /*ScalingStatValue*/, ScalingStatValuesEntry const* /*ssv*/) { }

        //[[nodiscard]] virtual bool CanArmorDamageModifier(Player* /*player*/) { return true; }

        //public static int OnGetFeralApBonus(Player* /*player*/, int32& /*feral_bonus*/, int32 /*dpsMod*/, ItemTemplate const* /*proto*/, ScalingStatValuesEntry const* /*ssv*/) { }

        //[nodiscard] virtual bool CanApplyWeaponDependentAuraDamageMod(Player* /*player*/, Item* /*item*/, WeaponAttackType /*attackType*/, AuraEffect const* /*aura*/, bool /*apply*/) { return true; }

        //[[nodiscard]] virtual bool CanApplyEquipSpell(Player* /*player*/, SpellInfo const* /*spellInfo*/, Item* /*item*/, bool /*apply*/, bool /*form_change*/) { return true; }

        //[[nodiscard]] virtual bool CanApplyEquipSpellsItemSet(Player* /*player*/, ItemSetEffect* /*eff*/) { return true; }

        //[[nodiscard]] virtual bool CanCastItemCombatSpell(Player* /*player*/, Unit* /*target*/, WeaponAttackType /*attType*/, uint32 /*procVictim*/, uint32 /*procEx*/, Item* /*item*/, ItemTemplate const* /*proto*/) { return true; }

        //[[nodiscard]] virtual bool CanCastItemUseSpell(Player* /*player*/, Item* /*item*/, SpellCastTargets const& /*targets*/, uint8 /*cast_count*/, uint32 /*glyphIndex*/) { return true; }

        //virtual void OnApplyAmmoBonuses(Player* /*player*/, ItemTemplate const* /*proto*/, float& /*currentAmmoDPS*/) { }

        //[[nodiscard]] virtual bool CanEquipItem(Player* /*player*/, uint8 /*slot*/, uint16& /*dest*/, Item* /*pItem*/, bool /*swap*/, bool /*not_loading*/) { return true; }

        //[[nodiscard]] virtual bool CanUnequipItem(Player* /*player*/, uint16 /*pos*/, bool /*swap*/) { return true; }

        //[[nodiscard]] virtual bool CanUseItem(Player* /*player*/, ItemTemplate const* /*proto*/, InventoryResult& /*result*/) { return true; }

        //[[nodiscard]] virtual bool CanSaveEquipNewItem(Player* /*player*/, Item* /*item*/, uint16 /*pos*/, bool /*update*/) { return true; }

        //[[nodiscard]] virtual bool CanApplyEnchantment(Player* /*player*/, Item* /*item*/, EnchantmentSlot /*slot*/, bool /*apply*/, bool /*apply_dur*/, bool /*ignore_condition*/) { return true; }

        //virtual void OnGetQuestRate(Player* /*player*/, float& /*result*/) { }

        //[[nodiscard]] virtual bool PassedQuestKilledMonsterCredit(Player* /*player*/, Quest const* /*qinfo*/, uint32 /*entry*/, uint32 /*real_entry*/, ObjectGuid /*guid*/) { return true; }

        //[[nodiscard]] virtual bool CheckItemInSlotAtLoadInventory(Player* /*player*/, Item* /*item*/, uint8 /*slot*/, uint8& /*err*/, uint16& /*dest*/) { return true; }

        //[[nodiscard]] virtual bool NotAvoidSatisfy(Player* /*player*/, DungeonProgressionRequirements const* /*ar*/, uint32 /*target_map*/, bool /*report*/) { return true; }

        //[[nodiscard]] virtual bool NotVisibleGloballyFor(Player* /*player*/, Player const* /*u*/) { return true; }

        //virtual void OnGetArenaPersonalRating(Player* /*player*/, uint8 /*slot*/, uint32& /*result*/) { }

        //virtual void OnGetArenaTeamId(Player* /*player*/, uint8 /*slot*/, uint32& /*result*/) { }

        //virtual void OnIsFFAPvP(Player* /*player*/, bool& /*result*/) { }

        //virtual void OnIsPvP(Player* /*player*/, bool& /*result*/) { }

        //virtual void OnGetMaxSkillValueForLevel(Player* /*player*/, uint16& /*result*/) { }

        //[[nodiscard]] virtual bool NotSetArenaTeamInfoField(Player* /*player*/, uint8 /*slot*/, ArenaTeamInfoType /*type*/, uint32 /*value*/) { return true; }

        //[[nodiscard]] virtual bool CanJoinLfg(Player* /*player*/, uint8 /*roles*/, lfg::LfgDungeonSet& /*dungeons*/, const std::string& /*comment*/) { return true; }

        //[[nodiscard]] virtual bool CanEnterMap(Player* /*player*/, MapEntry const* /*entry*/, InstanceTemplate const* /*instance*/, MapDifficulty const* /*mapDiff*/, bool /*loginCheck*/) { return true; }

        //[[nodiscard]] virtual bool CanInitTrade(Player* /*player*/, Player* /*target*/) { return true; }

        //virtual void OnSetServerSideVisibility(Player* /*player*/, ServerSideVisibilityType& /*type*/, AccountTypes& /*sec*/) { }

        //virtual void OnSetServerSideVisibilityDetect(Player* /*player*/, ServerSideVisibilityType& /*type*/, AccountTypes& /*sec*/) { }

        //virtual void OnPlayerResurrect(Player* /*player*/, float /*restore_percent*/, bool /*applySickness*/) { }

        /**
         * @brief This hook called before player sending message in default chat
         *
         * @param player Contains information about the Player sender
         * @param type Contains information about the chat message type
         * @param language Contains information about the language type
         * @param msg Contains information about the message
         *
         * @return True if you want to continue sending the message, false if you want to disable sending the message
         */
        //[[nodiscard]] virtual bool CanPlayerUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/) { return true; }

        /**
         * @brief This hook called before player sending message to other player via private
         *
         * @param player Contains information about the Player sender
         * @param type Contains information about the chat message type
         * @param language Contains information about the language type
         * @param msg Contains information about the message
         * @param receiver Contains information about the Player receiver
         *
         * @return True if you want to continue sending the message, false if you want to disable sending the message
         */
        //[[nodiscard]] virtual bool CanPlayerUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Player* /*receiver*/) { return true; }

        /**
         * @brief This hook called before player sending message to group
         *
         * @param player Contains information about the Player sender
         * @param type Contains information about the chat message type
         * @param language Contains information about the language type
         * @param msg Contains information about the message
         * @param group Contains information about the Group
         *
         * @return True if you want to continue sending the message, false if you want to disable sending the message
         */
        //[[nodiscard]] virtual bool CanPlayerUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Group* /*group*/) { return true; }

        /**
         * @brief This hook called before player sending message to guild
         *
         * @param player Contains information about the Player sender
         * @param type Contains information about the chat message type
         * @param language Contains information about the language type
         * @param msg Contains information about the message
         * @param guild Contains information about the Guild
         *
         * @return True if you want to continue sending the message, false if you want to disable sending the message
         */
        //[[nodiscard]] virtual bool CanPlayerUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Guild* /*guild*/) { return true; }

        /**
         * @brief This hook called before player sending message to channel
         *
         * @param player Contains information about the Player sender
         * @param type Contains information about the chat message type
         * @param language Contains information about the language type
         * @param msg Contains information about the message
         * @param channel Contains information about the Channel
         *
         * @return True if you want to continue sending the message, false if you want to disable sending the message
         */
        //[[nodiscard]] virtual bool CanPlayerUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Channel* /*channel*/) { return true; }

        /**
         * @brief This hook called after player learning talents
         *
         * @param player Contains information about the Player
         * @param talentId Contains information about the talent id
         * @param talentRank Contains information about the talent rank
         * @param spellid Contains information about the spell id
         */
        //virtual void OnPlayerLearnTalents(Player* /*player*/, uint32 /*talentId*/, uint32 /*talentRank*/, uint32 /*spellid*/) { }

        /**
         * @brief This hook called after player entering combat
         *
         * @param player Contains information about the Player
         * @param Unit Contains information about the Unit
         */
        //virtual void OnPlayerEnterCombat(Player* /*player*/, Unit* /*enemy*/) { }

        /**
         * @brief This hook called after player leave combat
         *
         * @param player Contains information about the Player
         */
        //virtual void OnPlayerLeaveCombat(Player* /*player*/) { }

        /**
         * @brief This hook called after player abandoning quest
         *
         * @param player Contains information about the Player
         * @param questId Contains information about the quest id
         */
        //virtual void OnQuestAbandon(Player* /*player*/, uint32 /*questId*/) { }

        // Passive Anticheat System
        //virtual void AnticheatSetSkipOnePacketForASH(Player* /*player*/, bool /*apply*/) { }
        //virtual void AnticheatSetCanFlybyServer(Player* /*player*/, bool /*apply*/) { }
        //virtual void AnticheatSetUnderACKmount(Player* /*player*/) { }
        //virtual void AnticheatSetRootACKUpd(Player* /*player*/) { }
        //virtual void AnticheatSetJumpingbyOpcode(Player* /*player*/, bool /*jump*/) { }
        //virtual void AnticheatUpdateMovementInfo(Player* /*player*/, MovementInfo const& /*movementInfo*/) { }
        //[[nodiscard]] virtual bool AnticheatHandleDoubleJump(Player* /*player*/, Unit* /*mover*/) { return true; }
        //[[nodiscard]] virtual bool AnticheatCheckMovementInfo(Player* /*player*/, MovementInfo const& /*movementInfo*/, Unit* /*mover*/, bool /*jump*/) { return true; }

    }
}
