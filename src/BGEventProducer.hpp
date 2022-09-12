
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
    class BGEventProducer : public BGScript
    {

    public:
        RdKafka::Producer* _producer;

        BGEventProducer(RdKafka::Producer* producer) : BGScript("BGEventProducer") {
            _producer = producer;
        }
        /**
 * @brief This hook runs before start Battleground
 *
 * @param bg Contains information about the Battleground
 */
        void OnBattlegroundStart(Battleground* bg)  override { }

        // End Battleground
        void OnBattlegroundEndReward(Battleground* bg, Player* player, TeamId winnerTeamId)  override { }

        // Update Battlegroud
        void OnBattlegroundUpdate(Battleground* bg, uint32 diff)  override { }

        // Add Player in Battlegroud
        void OnBattlegroundAddPlayer(Battleground* bg, Player* player)  override { }

        // Before added player in Battlegroud
        void OnBattlegroundBeforeAddPlayer(Battleground* bg, Player* player)  override { }

        // Remove player at leave BG
        void OnBattlegroundRemovePlayerAtLeave(Battleground* bg, Player* player)  override { }

        void OnQueueUpdate(BattlegroundQueue* queue, uint32  diff , BattlegroundTypeId  bgTypeId , BattlegroundBracketId  bracket_id , uint8  arenaType , bool  isRated , uint32  arenaRating ) override { }

        void OnAddGroup(BattlegroundQueue* queue, GroupQueueInfo* ginfo, uint32& index, Player* leader, Group* group, BattlegroundTypeId  bgTypeId , PvPDifficultyEntry const*  bracketEntry ,
            uint8  arenaType , bool  isRated , bool  isPremade , uint32  arenaRating , uint32  matchmakerRating , uint32  arenaTeamId , uint32  opponentsArenaTeamId ) override { }

        bool CanFillPlayersToBG(BattlegroundQueue* queue, Battleground* bg, BattlegroundBracketId bracket_id) override{ return true; }

        bool IsCheckNormalMatch(BattlegroundQueue* queue, Battleground* bgTemplate, BattlegroundBracketId bracket_id, uint32 minPlayers, uint32 maxPlayers)override { return false; };

        bool CanSendMessageBGQueue(BattlegroundQueue* queue, Player* leader, Battleground* bg, PvPDifficultyEntry const* bracketEntry) override{ return true; }

        /**
         * @brief This hook runs before sending the join message during the arena queue, allowing you to run extra operations or disabling the join message
         *
         * @param queue Contains information about the Arena queue
         * @param leader Contains information about the player leader
         * @param ginfo Contains information about the group of the queue
         * @param bracketEntry Contains information about the bracket
         * @param isRated Contains information about rated arena or skirmish
         * @return True if you want to continue sending the message, false if you want to disable the message
         */
        bool OnBeforeSendJoinMessageArenaQueue(BattlegroundQueue* queue, Player* leader, GroupQueueInfo* ginfo, PvPDifficultyEntry const* bracketEntry, bool isRated)override { return true; }

        /**
         * @brief This hook runs before sending the exit message during the arena queue, allowing you to run extra operations or disabling the exit message
         *
         * @param queue Contains information about the Arena queue
         * @param ginfo Contains information about the group of the queue
         * @return True if you want to continue sending the message, false if you want to disable the message
         */
        bool OnBeforeSendExitMessageArenaQueue(BattlegroundQueue* queue, GroupQueueInfo* ginfo) override { return true; }

        /**
         * @brief This hook runs after end Battleground
         *
         * @param bg Contains information about the Battleground
         * @param TeamId Contains information about the winneer team
         */
        void OnBattlegroundEnd(Battleground* bg, TeamId winnerTeam)  override { }

        /**
         * @brief This hook runs before Battleground destroy
         *
         * @param bg Contains information about the Battleground
         */
        void OnBattlegroundDestroy(Battleground* bg)  override { }

        /**
         * @brief This hook runs after Battleground create
         *
         * @param bg Contains information about the Battleground
         */
        void OnBattlegroundCreate(Battleground* bg) override{ }

    };
}
