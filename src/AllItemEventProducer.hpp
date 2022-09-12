
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
    class AllItemEventProducer : public AllItemScript
    {

    public:
        RdKafka::Producer* _producer;

        AllItemEventProducer(RdKafka::Producer* producer) : AllItemScript("AllItemEventProducer") {
            _producer = producer;
        }
        
        // Called when a player selects an option in an item gossip window
        void OnItemGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override { }

        // Called when a player selects an option in an item gossip window
        void OnItemGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char* code) override { }

    };
}
