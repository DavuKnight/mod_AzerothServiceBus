
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
        void OnCreate(InstanceMap* map) override { }

        // Called just before the map is destroyed.
        void OnDestroy(InstanceMap* map) override { }

        // Called when a grid map is loaded.
        void OnLoadGridMap(InstanceMap* map, GridMap* gmap, uint32 gx, uint32 gy) override { }

        // Called when a grid map is unloaded.
        void OnUnloadGridMap(InstanceMap* map, GridMap* gmap, uint32 gx, uint32 gy) override { }

        // Called when a player enters the map.
        void OnPlayerEnter(InstanceMap* map, Player* player) override { }

        // Called when a player leaves the map.
        void OnPlayerLeave(InstanceMap* map, Player* player) override { }

        // Called on every map update tick.
        void OnUpdate(InstanceMap* map, uint32 diff) override { }
    };
}
