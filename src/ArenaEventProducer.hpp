
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
    class ArenaEventProducer : public ArenaScript
    {

    public:
        RdKafka::Producer* _producer;

        ArenaEventProducer(RdKafka::Producer* producer) : ArenaScript("ArenaEventProducer") {
            _producer = producer;
        }
        void OnGetPoints(ArenaTeam* team, uint32 memberRating, float& points) override{ }

    };
}
