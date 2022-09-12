
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
    class AreaTriggerEventProducer : public AreaTriggerScript
    {

    public:
        RdKafka::Producer* _producer;

        AreaTriggerEventProducer(RdKafka::Producer* producer) : AreaTriggerScript("AreaTriggerEventProducer") {
            _producer = producer;
        }
        // Called when the area trigger is activated by a player.
        bool OnTrigger(Player* player, AreaTrigger const* trigger) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"trigger",boost::json::value_from(trigger) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AreaTriggerScript.OnTrigger", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
