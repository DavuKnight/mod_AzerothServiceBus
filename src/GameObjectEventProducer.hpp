
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
    class GameObjectEventProducer : public GameObjectScript
    {

    public:
        RdKafka::Producer* _producer;

        GameObjectEventProducer(RdKafka::Producer* producer) : GameObjectScript("GameObjectEventProducer") {
            _producer = producer;
        }
        // Called when a player opens a gossip dialog with the gameobject.
        virtual bool OnGossipHello(Player* player, GameObject* go)override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"go",boost::json::value_from(go) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameObjectScript.OnGossipHello", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
         return false; }

        // Called when a player selects a gossip item in the gameobject's gossip menu.
        bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action)override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"go",boost::json::value_from(go) },
                    {"sender",boost::json::value_from(sender) },
                    {"action",boost::json::value_from(action) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameObjectScript.OnGossipSelect", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
         return false; }

        // Called when a player selects a gossip with a code in the gameobject's gossip menu.
        bool OnGossipSelectCode(Player* player, GameObject* go, uint32 sender, uint32 action, const char* code)override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"go",boost::json::value_from(go) },
                    {"sender",boost::json::value_from(sender) },
                    {"action",boost::json::value_from(action) },
                    {"code",code }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameObjectScript.OnGossipSelectCode", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
         return false; }

        // Called when a player accepts a quest from the gameobject.
        bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest)override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"go",boost::json::value_from(go) },
                    {"quest",boost::json::value_from(quest) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameObjectScript.OnQuestAccept", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
         return false; }

        // Called when a player selects a quest reward.
        bool OnQuestReward(Player* player, GameObject* go, Quest const* quest, uint32 opt)override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"go",boost::json::value_from(go) },
                    {"quest",boost::json::value_from(quest) },
                    {"opt",boost::json::value_from(opt) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameObjectScript.OnQuestReward", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
         return false; }

    };
}
