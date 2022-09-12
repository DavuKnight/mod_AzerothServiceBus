
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
    class WeatherEventProducer : public WeatherScript
    {

    public:
        RdKafka::Producer* _producer;

        WeatherEventProducer(RdKafka::Producer* producer) : WeatherScript("WeatherEventProducer") {
            _producer = producer;
        }
        void OnChange(Weather* weather, WeatherState state, float grade)override
        {
            try
            {
                boost::json::value jv = {
                    {"weather",boost::json::value_from(weather) },
                    {"state",boost::json::value_from(state) },
                    {"grade",boost::json::value_from(grade) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WeatherScript.OnChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
