
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
    class WorldMapEventProducer : public WorldMapScript
    {

    public:
        RdKafka::Producer* _producer;
        //Will need to create one for each mapId we want to script;
        WorldMapEventProducer(RdKafka::Producer* producer,uint32 mapId) : WorldMapScript("WorldMapEventProducer", mapId) {
            _producer = producer;
        }
    };
}
