
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
    class VehicleEventProducer : public VehicleScript
    {

    public:
        RdKafka::Producer* _producer;

        VehicleEventProducer(RdKafka::Producer* producer) : VehicleScript("VehicleEventProducer") {
            _producer = producer;
        }

        // Called after a vehicle is installed.
        void OnInstall(Vehicle* veh) override
        {
            try
            {
                boost::json::value jv = {
                    {"object",boost::json::value_from(veh) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("VehicleScript.OnInstall", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called after a vehicle is uninstalled.
        void OnUninstall(Vehicle* veh) override
        {
            try
            {
                boost::json::value jv = {
                    {"veh",boost::json::value_from(veh) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("VehicleScript.OnUninstall", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when a vehicle resets.
        void OnReset(Vehicle* veh) override
        {
            try
            {
                boost::json::value jv = {
                    {"veh",boost::json::value_from(veh) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("VehicleScript.OnReset", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called after an accessory is installed in a vehicle.
        void OnInstallAccessory(Vehicle* veh, Creature* accessory) override
        {
            try
            {
                boost::json::value jv = {
                    {"veh",boost::json::value_from(veh) },
                    {"accessory",boost::json::value_from(accessory) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("VehicleScript.OnInstallAccessory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called after a passenger is added to a vehicle.
        void OnAddPassenger(Vehicle* veh, Unit* passenger, int8 seatId) override
        {
            try
            {
                boost::json::value jv = {
                    {"veh",boost::json::value_from(veh) },
                    {"passenger",boost::json::value_from(passenger) },
                    {"seatId",boost::json::value_from(seatId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("VehicleScript.OnAddPassenger", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called after a passenger is removed from a vehicle.
        void OnRemovePassenger(Vehicle* veh, Unit* passenger) override
        {
            try
            {
                boost::json::value jv = {
                    {"veh",boost::json::value_from(veh) },
                    {"passenger",boost::json::value_from(passenger) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("VehicleScript.OnRemovePassenger", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
