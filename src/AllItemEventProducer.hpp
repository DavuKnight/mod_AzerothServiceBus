
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
    class AllItemEventProducer : public AllItemScript
    {

    public:
        RdKafka::Producer* _producer;

        AllItemEventProducer(RdKafka::Producer* producer) : AllItemScript("AllItemEventProducer") {
            _producer = producer;
        }
        
        // Called when a player selects an option in an item gossip window
        void OnItemGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"item",boost::json::value_from(item) },
                    {"sender",boost::json::value_from(sender) },
                    {"action",boost::json::value_from(action) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllItemScript.OnItemGossipSelect", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when a player selects an option in an item gossip window
        void OnItemGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char* code) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"item",boost::json::value_from(item) },
                    {"sender",boost::json::value_from(sender) },
                    {"action",boost::json::value_from(action) },
                    {"code",code }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllItemScript.OnItemGossipSelectCode", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
