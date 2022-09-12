
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
    class AchievementEventProducer : public AchievementScript
    {

    public:
        RdKafka::Producer* _producer;

        AchievementEventProducer(RdKafka::Producer* producer) : AchievementScript("AchievementEventProducer") {
            _producer = producer;
        }

        // After complete global acvievement
        void SetRealmCompleted(AchievementEntry const* achievement) override { }

    };
}
