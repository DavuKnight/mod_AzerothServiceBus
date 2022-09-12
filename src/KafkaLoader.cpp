#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>

#if _AIX
#include <unistd.h>
#endif

/*
 * Typical include path in a real application would be
 * #include <librdkafka/rdkafkacpp.h>
 */
#include "../deps/librdkafka-1.8.2/src-cpp/rdkafkacpp.h"
#include <boost/json/src.hpp>
#include "AccountEventProducer.hpp"
#include "AchievementCriteriaEventProducer.hpp"
#include "AchievementEventProducer.hpp"
#include "AllCreatureEventProducer.hpp"
#include "AllGameObjectEventProducer.hpp"
#include "AllItemEventProducer.hpp"
#include "AllMapEventProducer.hpp"
#include "AreaTriggerEventProducer.hpp"
#include "ArenaEventProducer.hpp"
#include "ArenaTeamEventProducer.hpp"
#include "AuctionHouseEventProducer.hpp"
#include "BattlegroundEventProducer.hpp"
#include "BattlegroundMapEventProducer.hpp"
#include "BGEventProducer.hpp"
#include "CommandEventProducer.hpp"
#include "ConditionEventProducer.hpp"
#include "CreatureEventProducer.hpp"
#include "GameEventEventProducer.hpp"
#include "GameObjectEventProducer.hpp"
#include "GlobalEventProducer.hpp"
#include "GroupEventProducer.hpp"
#include "GuildEventProducer.hpp"
#include "InstanceMapEventProducer.hpp"
#include "ItemEventProducer.hpp"
#include "LootEventProducer.hpp"
#include "MailEventProducer.hpp"
#include "Map_InstanceMapEventProducer.hpp"
#include "Map_MapEventProducer.hpp"
#include "Map_BattlegroundEventProducer.hpp"
#include "MiscEventProducer.hpp"
#include "OnlyOnceAreaTriggerEventProducer.hpp"
#include "OutdoorPvPEventProducer.hpp"
#include "PetEventProducer.hpp"
#include "PlayerEventProducer.hpp"
#include "TransportEventProducer.hpp"
#include "UnitEventProducer.hpp"
#include "VehicleEventProducer.hpp"
#include "WeatherEventProducer.hpp"
#include "WorldEventProducer.hpp"
#include "WorldMapEventProducer.hpp"
#include "WorldObjectEventProducer.hpp"


using namespace RdKafka;



// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void Addmod_AzerothServiceBusScripts()
{
    std::string Server = "127.0.0.1";


    /*
     * Create configuration object
     */
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    std::string errstr;

    /* Set bootstrap broker(s) as a comma-separated list of
     * host or host:port (default port 9092).
     * librdkafka will use the bootstrap brokers to acquire the full
     * set of brokers from the cluster. */
    if (conf->set("bootstrap.servers", Server, errstr) !=
        RdKafka::Conf::CONF_OK) {
        std::cerr << errstr << std::endl;
        exit(1);
    }

    //signal(SIGINT, sigterm);
    //signal(SIGTERM, sigterm);

     /*
      * Create producer instance.
      */
    RdKafka::Producer* producer = RdKafka::Producer::create(conf, errstr);
    if (!producer) {
        std::cerr << "Failed to create producer: " << errstr << std::endl;
        exit(1);
    }

    new mod_AzerothServiceBus::PlayerEventProducer(producer);
    new mod_AzerothServiceBus::WorldEventProducer(producer);


}

/* Use of this partitioner is pretty pointless since no key is provided
 * in the produce() call. */
class MyHashPartitionerCb : public PartitionerCb
{
public:
    int32_t partitioner_cb(const Topic* topic, const std::string* key,
        int32_t partition_cnt, void* msg_opaque) {
        return djb_hash(key->c_str(), key->size()) % partition_cnt;
    }
private:

    static inline unsigned int djb_hash(const char* str, size_t len) {
        unsigned int hash = 5381;
        for (size_t i = 0; i < len; i++)
            hash = ((hash << 5) + hash) + str[i];
        return hash;
    }
};

