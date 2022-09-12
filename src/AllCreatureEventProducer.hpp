
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
    class AllCreatureEventProducer : public AllCreatureScript
    {

    public:
        RdKafka::Producer* _producer;

        AllCreatureEventProducer(RdKafka::Producer* producer) : AllCreatureScript("AllCreatureEventProducer") {
            _producer = producer;
        }
        // Called from End of Creature Update.
        void OnAllCreatureUpdate(Creature* creature, uint32 diff) override{ }

        // Called from End of Creature SelectLevel.
        void Creature_SelectLevel(const CreatureTemplate* cinfo, Creature* creature) override { }

        /**
         * @brief This hook runs after add creature in world
         *
         * @param creature Contains information about the Creature
         */
        void OnCreatureAddWorld(Creature* creature) override{ }

        /**
         * @brief This hook runs after remove creature in world
         *
         * @param creature Contains information about the Creature
         */
        void OnCreatureRemoveWorld(Creature* creature) override{ }

        /**
         * @brief This hook runs after creature has been saved to DB
         *
         * @param creature Contains information about the Creature
        */
         void OnCreatureSaveToDB(Creature* creature) override{ }
    };
}
