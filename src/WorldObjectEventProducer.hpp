
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
    class WorldObjectEventProducer : public WorldObjectScript
    {

    public:
        RdKafka::Producer* _producer;

        WorldObjectEventProducer(RdKafka::Producer* producer) : WorldObjectScript("WorldObjectEventProducer")
        {
            _producer = producer;
        }

        /**
         * @brief This hook called before destroy world object
         *
         * @param object Contains information about the WorldObject
         */
        void OnWorldObjectDestroy(WorldObject* object) override
        {
            try
            {
                boost::json::value jv = {
                    {"object",boost::json::value_from(object) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectDestroy", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called after create world object
         *
         * @param object Contains information about the WorldObject
         */
        void OnWorldObjectCreate(WorldObject* object) override
        {
            try
            {
                boost::json::value jv = {
                    {"object",boost::json::value_from(object) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectCreate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called after world object set to map
         *
         * @param object Contains information about the WorldObject
         */
        void OnWorldObjectSetMap(WorldObject* object, Map* map) override
        {
            try
            {
                boost::json::value jv = {
                    {"object",boost::json::value_from(object) },
                    {"map",boost::json::value_from(map) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectSetMap", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called after world object reset
         *
         * @param object Contains information about the WorldObject
         */
        void OnWorldObjectResetMap(WorldObject* object) override
        {
            try
            {
                boost::json::value jv = {
                    {"object",boost::json::value_from(object) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("WorldObjectScript.OnWorldObjectResetMap", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called after world object update
         *
         * @param object Contains information about the WorldObject
         * @param diff Contains information about the diff time
         */
        void OnWorldObjectUpdate(WorldObject* object, uint32 diff) override
        {
            try
            {
                boost::json::value jv = {
                    {"object",boost::json::value_from(object) },
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


    };
}
