
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
    class GameEventEventProducer : public GameEventScript
    {

    public:
        RdKafka::Producer* _producer;

        GameEventEventProducer(RdKafka::Producer* producer) : GameEventScript("GameEventEventProducer") {
            _producer = producer;
        }

        // Runs on start event
        void OnStart(uint16 EventID) override
        {
            try
            {
                boost::json::value jv = {
                    {"EventID",boost::json::value_from(EventID) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameEventScript.OnStart", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Runs on stop event
        void OnStop(uint16 EventID) override
        {
            try
            {
                boost::json::value jv = {
                    {"EventID",boost::json::value_from(EventID) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameEventScript.OnStop", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Runs on event check
        void OnEventCheck(uint16 EventID)override
        {
            try
            {
                boost::json::value jv = {
                    {"EventID",boost::json::value_from(EventID) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GameEventScript.OnEventCheck", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
