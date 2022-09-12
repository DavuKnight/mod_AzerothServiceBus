
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
    class CreatureEventProducer : public CreatureScript
    {

    public:
        RdKafka::Producer* _producer;

        CreatureEventProducer(RdKafka::Producer* producer) : CreatureScript("CreatureEventProducer") {
            _producer = producer;
        }

        // Called when a player opens a gossip dialog with the creature.
        bool OnGossipHello(Player* player, Creature* creature)
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"creature",boost::json::value_from(creature) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("CreatureScript.OnGossipHello", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a player selects a gossip item in the creature's gossip menu.
        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"creature",boost::json::value_from(creature) },
                    {"sender",boost::json::value_from(sender) },
                    {"action",boost::json::value_from(action) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("CreatureScript.OnGossipSelect", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a player selects a gossip with a code in the creature's gossip menu.
        bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"creature",boost::json::value_from(creature) },
                    {"sender",boost::json::value_from(sender) },
                    {"action",boost::json::value_from(action) },
                    {"code",code }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("CreatureScript.OnGossipSelectCode", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a player accepts a quest from the creature.
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"creature",boost::json::value_from(creature) },
                    {"quest",boost::json::value_from(quest) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("CreatureScript.OnQuestAccept", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a player selects a quest in the creature's quest menu.
        bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest)
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"creature",boost::json::value_from(creature) },
                    {"quest",boost::json::value_from(quest) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("CreatureScript.OnQuestSelect", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a player completes a quest with the creature.
        bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"creature",boost::json::value_from(creature) },
                    {"quest",boost::json::value_from(quest) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("CreatureScript.OnQuestComplete", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"creature",boost::json::value_from(creature) },
                    {"quest",boost::json::value_from(quest) },
                    {"opt",boost::json::value_from(opt) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("CreatureScript.OnQuestReward", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
