
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
    class LootEventProducer : public LootScript
    {

    public:
        RdKafka::Producer* _producer;

        LootEventProducer(RdKafka::Producer* producer) : LootScript("LootEventProducer") {
            _producer = producer;
        }

        /**
         * @brief This hook called before money loot
         *
         * @param player Contains information about the Player
         * @param gold Contains information about money
         */
        void OnLootMoney(Player* player, uint32 gold)override { }
    };
}
