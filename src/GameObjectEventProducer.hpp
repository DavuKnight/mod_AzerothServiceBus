
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
    class GameObjectEventProducer : public GameObjectScript
    {

    public:
        RdKafka::Producer* _producer;

        GameObjectEventProducer(RdKafka::Producer* producer) : GameObjectScript("GameObjectEventProducer") {
            _producer = producer;
        }
        // Called when a player opens a gossip dialog with the gameobject.
        virtual bool OnGossipHello(Player* player, GameObject* go)override { return false; }

        // Called when a player selects a gossip item in the gameobject's gossip menu.
        bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action)override { return false; }

        // Called when a player selects a gossip with a code in the gameobject's gossip menu.
        bool OnGossipSelectCode(Player* player, GameObject* go, uint32 sender, uint32 action, const char* code)override { return false; }

        // Called when a player accepts a quest from the gameobject.
        bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest)override { return false; }

        // Called when a player selects a quest reward.
        bool OnQuestReward(Player* player, GameObject* go, Quest const* quest, uint32 opt)override { return false; }

    };
}
