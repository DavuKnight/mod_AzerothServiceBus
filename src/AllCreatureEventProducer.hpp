
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
    class AllCreatureEventProducer : public AllCreatureScript
    {

    public:
        RdKafka::Producer* _producer;

        AllCreatureEventProducer(RdKafka::Producer* producer) : AllCreatureScript("AllCreatureEventProducer") {
            _producer = producer;
        }
        // Called from End of Creature Update.
        void OnAllCreatureUpdate(Creature* creature, uint32 diff) override
        {
            try
            {
                boost::json::value jv = {
                    {"creature",boost::json::value_from(creature) },
                    {"diff",boost::json::value_from(diff) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllCreatureScript.OnAllCreatureUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called from End of Creature SelectLevel.
        void Creature_SelectLevel(const CreatureTemplate* cinfo, Creature* creature) override
        {
            try
            {
                boost::json::value jv = {
                    {"creature",boost::json::value_from(creature) },
                    {"cinfo",boost::json::value_from(cinfo) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllCreatureScript.Creature_SelectLevel", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook runs after add creature in world
         *
         * @param creature Contains information about the Creature
         */
        void OnCreatureAddWorld(Creature* creature) override
        {
            try
            {
                boost::json::value jv = {
                    {"creature",boost::json::value_from(creature) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllCreatureScript.OnCreatureAddWorld", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook runs after remove creature in world
         *
         * @param creature Contains information about the Creature
         */
        void OnCreatureRemoveWorld(Creature* creature) override
        {
            try
            {
                boost::json::value jv = {
                    {"creature",boost::json::value_from(creature) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllCreatureScript.OnCreatureRemoveWorld", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook runs after creature has been saved to DB
         *
         * @param creature Contains information about the Creature
        */
         void OnCreatureSaveToDB(Creature* creature) override
         {
             try
             {
                 boost::json::value jv = {
                    {"creature",boost::json::value_from(creature) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllCreatureScript.OnCreatureSaveToDB", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
