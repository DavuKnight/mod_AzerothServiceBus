
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
        void OnInstall(Vehicle* veh) override { }

        // Called after a vehicle is uninstalled.
        void OnUninstall(Vehicle* veh) override { }

        // Called when a vehicle resets.
        void OnReset(Vehicle* veh) override { }

        // Called after an accessory is installed in a vehicle.
        void OnInstallAccessory(Vehicle* veh, Creature* accessory) override { }

        // Called after a passenger is added to a vehicle.
        void OnAddPassenger(Vehicle* veh, Unit* passenger, int8 seatId) override { }

        // Called after a passenger is removed from a vehicle.
        void OnRemovePassenger(Vehicle* veh, Unit* passenger) override{ }


    };
}
