
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
    class ConditionEventProducer : public ConditionScript
    {

    public:
        RdKafka::Producer* _producer;

        ConditionEventProducer(RdKafka::Producer* producer) : ConditionScript("ConditionEventProducer") {
            _producer = producer;
        }
    };
}
