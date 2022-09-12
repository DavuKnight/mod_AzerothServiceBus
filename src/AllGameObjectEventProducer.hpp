
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
        virtual void OnGameObjectAddWorld(GameObject* go) override{ }
        /**
         * @brief This hook runs after the game object iis saved to the database
         *
         * @param go Contains information about the GameObject
         */
        virtual void OnGameObjectSaveToDB(GameObject* go) override { }
        /**
         * @brief This hook runs after remove game object in world
         *
         * @param go Contains information about the GameObject
         */
        virtual void OnGameObjectRemoveWorld(GameObject* go) override{ }

        /**
         * @brief This hook runs after remove game object in world
         *
         * @param go Contains information about the GameObject
         */
        virtual void OnGameObjectUpdate(GameObject* go, uint32 diff) override{ }

        // Called when the game object is destroyed (destructible buildings only).
        virtual void OnGameObjectDestroyed(GameObject* go, Player* player) override{ }

        // Called when the game object is damaged (destructible buildings only).
        virtual void OnGameObjectDamaged(GameObject* go, Player* player) override{ }

        // Called when the game object loot state is changed.
        virtual void OnGameObjectLootStateChanged(GameObject* go, uint32 state, Unit* unit) override{ }

        // Called when the game object state is changed.
        virtual void OnGameObjectStateChanged(GameObject* go, uint32 state) override{ }

    };
}
