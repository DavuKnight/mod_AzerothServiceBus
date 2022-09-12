
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
    class AllMapEventProducer : public AllMapScript
    {

    public:
        RdKafka::Producer* _producer;

        AllMapEventProducer(RdKafka::Producer* producer) : AllMapScript("AllMapEventProducer") {
            _producer = producer;
        }

        /**
         * @brief This hook called when a player enters any Map
         *
         * @param map Contains information about the Map
         * @param player Contains information about the Player
         */
         void OnPlayerEnterAll(Map* map, Player* player) override
         {
             try
             {
                 boost::json::value jv = {
                     {"map",boost::json::value_from(map) },
                     {"player",boost::json::value_from(player) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllMapScript.OnPlayerEnterAll", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called when a player leave any Map
         *
         * @param map Contains information about the Map
         * @param player Contains information about the Player
         */
         void OnPlayerLeaveAll(Map* map, Player* player) override
         {
             try
             {
                 boost::json::value jv = {
                     {"map",boost::json::value_from(map) },
                     {"player",boost::json::value_from(player) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllMapScript.OnPlayerLeaveAll", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called before create instance script
         *
         * @param instanceMap Contains information about the WorldSession
         * @param instanceData Contains information about the WorldPacket
         * @param load if true loading instance save data
         * @param data Contains information about the instance save data
         * @param completedEncounterMask Contains information about the completed encouter mask
         */
         void OnBeforeCreateInstanceScript(InstanceMap* instanceMap, InstanceScript* instanceData, bool load, std::string data, uint32 completedEncounterMask) override
         {
             try
             {
                 boost::json::value jv = {
                     {"instanceMap",boost::json::value_from(instanceMap) },
                     {"instanceData",boost::json::value_from(instanceData) },
                     {"load",boost::json::value_from(load) },
                     {"data",boost::json::value_from(data) },
                     {"completedEncounterMask",boost::json::value_from(completedEncounterMask) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllMapScript.OnBeforeCreateInstanceScript", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called before destroy instance
         *
         * @param mapInstanced Contains information about the MapInstanced
         * @param map Contains information about the Map
         */
         void OnDestroyInstance(MapInstanced* mapInstanced, Map* map) override
         {
             try
             {
                 boost::json::value jv = {
                     {"mapInstanced",boost::json::value_from(mapInstanced) },
                     {"map",boost::json::value_from(map) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllMapScript.OnDestroyInstance", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called before creating map
         *
         * @param map Contains information about the Map
         */
         void OnCreateMap(Map* map) override
         {
             try
             {
                 boost::json::value jv = {
                     {"map",boost::json::value_from(map) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllMapScript.OnCreateMap", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called before destroing map
         *
         * @param map Contains information about the Map
         */
         void OnDestroyMap(Map* map) override
         {
             try
             {
                 boost::json::value jv = {
                     {"map",boost::json::value_from(map) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllMapScript.OnDestroyMap", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook called before updating map
         *
         * @param map Contains information about the Map
         * @param diff Contains information about the diff time
         */
         void OnMapUpdate(Map* map, uint32 diff) override
         {
             try
             {
                 boost::json::value jv = {
                     {"map",boost::json::value_from(map) },
                     {"diff",boost::json::value_from(diff) }
                 };
                 std::string body = serialize(jv);

                 RdKafka::ErrorCode resp = _producer->produce("AllMapScript.OnMapUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
