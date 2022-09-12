
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
    class AccountEventProducer : public AccountScript
    {

    public:
        RdKafka::Producer* _producer;

        AccountEventProducer(RdKafka::Producer* producer) : AccountScript("AccountEventProducer") {
            _producer = producer;
        }

        // Called when an account logged in successfully
        void OnAccountLogin (uint32 accountId) override{ }

        // Called when an ip logged in successfully
        void OnLastIpUpdate (uint32 accountId, std::string ip) override { }

        // Called when an account login failed
        void OnFailedAccountLogin (uint32 accountId)override { }

        // Called when Email is successfully changed for Account
        void OnEmailChange (uint32 accountId) override { }

        // Called when Email failed to change for Account
        void OnFailedEmailChange (uint32 accountId) override { }

        // Called when Password is successfully changed for Account
        void OnPasswordChange (uint32 accountId) override { }

        // Called when Password failed to change for Account
        void OnFailedPasswordChange (uint32 /*accountId*/) override { }
    };
}
