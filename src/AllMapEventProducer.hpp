
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
    class AllMapEventProducer : public AllMapScript
    {

    public:
        RdKafka::Producer* _producer;

        AllMapEventProducer(RdKafka::Producer* producer) : AllMapScript("AllMapEventProducer") {
            _producer = producer;
        }

        /**
         * @brief This hook called when a player enters any Map
         *
         * @param map Contains information about the Map
         * @param player Contains information about the Player
         */
         void OnPlayerEnterAll(Map* map, Player* player) override { }

        /**
         * @brief This hook called when a player leave any Map
         *
         * @param map Contains information about the Map
         * @param player Contains information about the Player
         */
         void OnPlayerLeaveAll(Map* map, Player* player) override{ }

        /**
         * @brief This hook called before create instance script
         *
         * @param instanceMap Contains information about the WorldSession
         * @param instanceData Contains information about the WorldPacket
         * @param load if true loading instance save data
         * @param data Contains information about the instance save data
         * @param completedEncounterMask Contains information about the completed encouter mask
         */
         void OnBeforeCreateInstanceScript(InstanceMap* instanceMap, InstanceScript* instanceData, bool load, std::string data, uint32 completedEncounterMask) override{ }

        /**
         * @brief This hook called before destroy instance
         *
         * @param mapInstanced Contains information about the MapInstanced
         * @param map Contains information about the Map
         */
         void OnDestroyInstance(MapInstanced* mapInstanced, Map* map) override { }

        /**
         * @brief This hook called before creating map
         *
         * @param map Contains information about the Map
         */
         void OnCreateMap(Map* map) override { }

        /**
         * @brief This hook called before destroing map
         *
         * @param map Contains information about the Map
         */
         void OnDestroyMap(Map* map) override { }

        /**
         * @brief This hook called before updating map
         *
         * @param map Contains information about the Map
         * @param diff Contains information about the diff time
         */
         void OnMapUpdate(Map* map, uint32 diff) override { }


    };
}
