
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
    class CreatureEventProducer : public CreatureScript
    {

    public:
        RdKafka::Producer* _producer;

        CreatureEventProducer(RdKafka::Producer* producer) : CreatureScript("CreatureEventProducer") {
            _producer = producer;
        }

        // Called when a player opens a gossip dialog with the creature.
        bool OnGossipHello(Player* player, Creature* creature) { return false; }

        // Called when a player selects a gossip item in the creature's gossip menu.
        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) { return false; }

        // Called when a player selects a gossip with a code in the creature's gossip menu.
        bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) { return false; }

        // Called when a player accepts a quest from the creature.
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) { return false; }

        // Called when a player selects a quest in the creature's quest menu.
        bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest) { return false; }

        // Called when a player completes a quest with the creature.
        bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest) { return false; }

        // Called when a player selects a quest reward.
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt) { return false; }
    };
}
