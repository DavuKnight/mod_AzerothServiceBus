
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
    class Map_BattlegroundEventProducer : public MapScript<Battleground>
    {

    public:
        RdKafka::Producer* _producer;

        Map_BattlegroundEventProducer(RdKafka::Producer* producer, uint32 mapid) : MapScript<Battleground>(mapid) {
            _producer = producer;
        }
        // Called when the map is created.
        void OnCreate(Battleground* map) override
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
        void OnDestroy(Battleground* map) override
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
        void OnLoadGridMap(Battleground* map, GridMap* gmap, uint32 gx, uint32 gy) override
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
        void OnUnloadGridMap(Battleground* map, GridMap* gmap, uint32 gx, uint32 gy) override
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
        void OnPlayerEnter(Battleground* map, Player* player) override
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
        void OnPlayerLeave(Battleground* map, Player* player) override
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
        //void OnUpdate(Battleground* map, uint32 diff) override
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
