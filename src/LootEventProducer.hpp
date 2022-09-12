
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
    class LootEventProducer : public LootScript
    {

    public:
        RdKafka::Producer* _producer;

        LootEventProducer(RdKafka::Producer* producer) : LootScript("LootEventProducer") {
            _producer = producer;
        }

        /**
         * @brief This hook called before money loot
         *
         * @param player Contains information about the Player
         * @param gold Contains information about money
         */
        void OnLootMoney(Player* player, uint32 gold)override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"gold",boost::json::value_from(gold) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MapScript.OnCreate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
