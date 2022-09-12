
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
    class ArenaEventProducer : public ArenaScript
    {

    public:
        RdKafka::Producer* _producer;

        ArenaEventProducer(RdKafka::Producer* producer) : ArenaScript("ArenaEventProducer") {
            _producer = producer;
        }
        void OnGetPoints(ArenaTeam* team, uint32 memberRating, float& points) override
        {
            try
            {
                boost::json::value jv = {
                    {"team",boost::json::value_from(team) },
                    {"memberRating",boost::json::value_from(memberRating) },
                    {"points",boost::json::value_from(points) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("ArenaScript.OnGetPoints", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
