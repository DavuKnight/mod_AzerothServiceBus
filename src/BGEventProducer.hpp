
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
        void OnBattlegroundStart(Battleground* bg)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // End Battleground
        void OnBattlegroundEndReward(Battleground* bg, Player* player, TeamId winnerTeamId)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) },
                    {"player",boost::json::value_from(player) },
                    {"winnerTeamId",boost::json::value_from(winnerTeamId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Update Battlegroud
        void OnBattlegroundUpdate(Battleground* bg, uint32 diff)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) },
                    {"diff",boost::json::value_from(diff) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Add Player in Battlegroud
        void OnBattlegroundAddPlayer(Battleground* bg, Player* player)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) },
                    {"player",boost::json::value_from(player) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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



        // Before added player in Battlegroud
        void OnBattlegroundBeforeAddPlayer(Battleground* bg, Player* player)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) },
                    {"player",boost::json::value_from(player) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Remove player at leave BG
        void OnBattlegroundRemovePlayerAtLeave(Battleground* bg, Player* player)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) },
                    {"player",boost::json::value_from(player) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnQueueUpdate(BattlegroundQueue* queue, uint32  diff , BattlegroundTypeId  bgTypeId , BattlegroundBracketId  bracket_id , uint8  arenaType , bool  isRated , uint32  arenaRating ) override
        {
            try
            {
                boost::json::value jv = {
                    {"queue",boost::json::value_from(queue) },
                    {"diff",boost::json::value_from(diff) },
                    {"bgTypeId",boost::json::value_from(bgTypeId) },
                    {"bracket_id",boost::json::value_from(bracket_id) },
                    {"arenaType",boost::json::value_from(arenaType) },
                    {"isRated",boost::json::value_from(isRated) },
                    {"arenaRating",boost::json::value_from(arenaRating) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnAddGroup(BattlegroundQueue* queue, GroupQueueInfo* ginfo, uint32& index, Player* leader, Group* group, BattlegroundTypeId  bgTypeId , PvPDifficultyEntry const*  bracketEntry ,
            uint8  arenaType , bool  isRated , bool  isPremade , uint32  arenaRating , uint32  matchmakerRating , uint32  arenaTeamId , uint32  opponentsArenaTeamId ) override
        {
            try
            {
                boost::json::value jv = {
                    {"queue",boost::json::value_from(queue) },
                    {"ginfo",boost::json::value_from(ginfo) },
                    {"index",boost::json::value_from(index) },
                    {"leader",boost::json::value_from(leader) },
                    {"group",boost::json::value_from(group) },
                    {"bgTypeId",boost::json::value_from(bgTypeId) },
                    {"bracketEntry",boost::json::value_from(bracketEntry) },
                    {"arenaType",boost::json::value_from(arenaType) },
                    {"isRated",boost::json::value_from(isRated) },
                    {"isPremade",boost::json::value_from(isPremade) },
                    {"arenaRating",boost::json::value_from(arenaRating) },
                    {"matchmakerRating",boost::json::value_from(matchmakerRating) },
                    {"arenaTeamId",boost::json::value_from(arenaTeamId) },
                    {"opponentsArenaTeamId",boost::json::value_from(opponentsArenaTeamId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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



        /**
         * @brief This hook runs after end Battleground
         *
         * @param bg Contains information about the Battleground
         * @param TeamId Contains information about the winneer team
         */
        void OnBattlegroundEnd(Battleground* bg, TeamId winnerTeam)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) },
                    {"winnerTeam",boost::json::value_from(winnerTeam) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        /**
         * @brief This hook runs before Battleground destroy
         *
         * @param bg Contains information about the Battleground
         */
        void OnBattlegroundDestroy(Battleground* bg)  override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        /**
         * @brief This hook runs after Battleground create
         *
         * @param bg Contains information about the Battleground
         */
        void OnBattlegroundCreate(Battleground* bg) override
        {
            try
            {
                boost::json::value jv = {
                    {"bg",boost::json::value_from(bg) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


    };
}
