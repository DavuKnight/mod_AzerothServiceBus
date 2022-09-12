
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
    class AllGameObjectEventProducer : public AllGameObjectScript
    {

    public:
        RdKafka::Producer* _producer;

        AllGameObjectEventProducer(RdKafka::Producer* producer) : AllGameObjectScript("AllGameObjectEventProducer") {
            _producer = producer;
        }
        /**
         * @brief This hook runs after add game object in world
         *
         * @param go Contains information about the GameObject
         */
        virtual void OnGameObjectAddWorld(GameObject* go) override
        {
            try
            {
                boost::json::value jv = {
                    {"go",boost::json::value_from(go) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectAddWorld", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook runs after the game object iis saved to the database
         *
         * @param go Contains information about the GameObject
         */
        virtual void OnGameObjectSaveToDB(GameObject* go) override
        {
            try
            {
                boost::json::value jv = {
                    {"go",boost::json::value_from(go) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectSaveToDB", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook runs after remove game object in world
         *
         * @param go Contains information about the GameObject
         */
        virtual void OnGameObjectRemoveWorld(GameObject* go) override
        {
            try
            {
                boost::json::value jv = {
                    {"go",boost::json::value_from(go) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectRemoveWorld", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
         * @brief This hook runs after remove game object in world
         *
         * @param go Contains information about the GameObject
         */
        virtual void OnGameObjectUpdate(GameObject* go, uint32 diff) override
        {
            try
            {
                boost::json::value jv = {
                    {"go",boost::json::value_from(go) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when the game object is destroyed (destructible buildings only).
        virtual void OnGameObjectDestroyed(GameObject* go, Player* player) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"go",boost::json::value_from(go) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectDestroyed", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when the game object is damaged (destructible buildings only).
        virtual void OnGameObjectDamaged(GameObject* go, Player* player) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(player) },
                    {"go",boost::json::value_from(go) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectDamaged", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when the game object loot state is changed.
        virtual void OnGameObjectLootStateChanged(GameObject* go, uint32 state, Unit* unit) override
        {
            try
            {
                boost::json::value jv = {
                    {"go",boost::json::value_from(go) },
                    {"state",boost::json::value_from(state) },
                    {"unit",boost::json::value_from(unit) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectLootStateChanged", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when the game object state is changed.
        virtual void OnGameObjectStateChanged(GameObject* go, uint32 state) override
        {
            try
            {
                boost::json::value jv = {
                    {"go",boost::json::value_from(go) },
                    {"state",boost::json::value_from(state) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AllGameObjectScript.OnGameObjectStateChanged", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
