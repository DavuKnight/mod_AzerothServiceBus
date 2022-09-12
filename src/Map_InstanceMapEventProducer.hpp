
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
    class Map_InstanceMapEventProducer : public MapScript<InstanceMap>
    {

    public:
        RdKafka::Producer* _producer;

        Map_InstanceMapEventProducer(RdKafka::Producer* producer, uint32 mapId) : MapScript<InstanceMap>(mapId) {
            _producer = producer;
        }
        // Called when the map is created.
        void OnCreate(InstanceMap* map) override
        {
            try
            {
                boost::json::value jv = {
                    {"map",boost::json::value_from(map) }
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


        // Called just before the map is destroyed.
        void OnDestroy(InstanceMap* map) override
        {
            try
            {
                boost::json::value jv = {
                    {"map",boost::json::value_from(map) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MapScript.OnDestroy", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when a grid map is loaded.
        void OnLoadGridMap(InstanceMap* map, GridMap* gmap, uint32 gx, uint32 gy) override
        {
            try
            {
                boost::json::value jv = {
                    {"map",boost::json::value_from(map) },
                    {"gmap",boost::json::value_from(gmap) },
                    {"gx",boost::json::value_from(gx) },
                    {"gy",boost::json::value_from(gy) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MapScript.OnLoadGridMap", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when a grid map is unloaded.
        void OnUnloadGridMap(InstanceMap* map, GridMap* gmap, uint32 gx, uint32 gy) override
        {
            try
            {
                boost::json::value jv = {
                    {"map",boost::json::value_from(map) },
                    {"gmap",boost::json::value_from(gmap) },
                    {"gx",boost::json::value_from(gx) },
                    {"gy",boost::json::value_from(gy) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MapScript.OnUnloadGridMap", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when a player enters the map.
        void OnPlayerEnter(InstanceMap* map, Player* player) override
        {
            try
            {
                boost::json::value jv = {
                    {"map",boost::json::value_from(map) },
                    {"player",boost::json::value_from(player) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MapScript.OnPlayerEnter", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when a player leaves the map.
        void OnPlayerLeave(InstanceMap* map, Player* player) override
        {
            try
            {
                boost::json::value jv = {
                    {"map",boost::json::value_from(map) },
                    {"player",boost::json::value_from(player) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MapScript.OnPlayerLeave", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        //// Called on every map update tick.
        //void OnUpdate(InstanceMap* map, uint32 diff) override
        //{
        //    try
        //    {
        //        boost::json::value jv = {
        //            {"map",boost::json::value_from(map) },
        //            {"diff",boost::json::value_from(diff) }
        //        };
        //        std::string body = serialize(jv);

        //        RdKafka::ErrorCode resp = _producer->produce("MapScript.OnUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //        if (resp != RdKafka::ERR_NO_ERROR) {
        //            std::cerr << "% Produce failed: " <<
        //                RdKafka::err2str(resp) << std::endl;
        //        }
        //        _producer->poll(0);
        //    }
        //    catch (...)
        //    {
        //    }
        //}


    };
}
