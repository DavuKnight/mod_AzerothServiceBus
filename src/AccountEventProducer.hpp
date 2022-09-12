
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
        void OnAccountLogin (uint32 accountId) override
        {
            try
            {
                boost::json::value jv = {
                   {"accountId",boost::json::value_from(accountId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AccountScript.OnAccountLogin", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        // Called when an ip logged in successfully
        void OnLastIpUpdate (uint32 accountId, std::string ip) override
        {
            try
            {
                boost::json::value jv = {
                   {"accountId",boost::json::value_from(accountId) },
                   {"ip",boost::json::value_from(ip) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AccountScript.OnLastIpUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        // Called when an account login failed
        void OnFailedAccountLogin (uint32 accountId)override
        {
            try
            {
                boost::json::value jv = {
                   {"accountId",boost::json::value_from(accountId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AccountScript.OnFailedAccountLogin", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        // Called when Email is successfully changed for Account
        void OnEmailChange (uint32 accountId) override
        {
            try
            {
                boost::json::value jv = {
                   {"accountId",boost::json::value_from(accountId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AccountScript.OnEmailChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        // Called when Email failed to change for Account
        void OnFailedEmailChange (uint32 accountId) override
        {
            try
            {
                boost::json::value jv = {
                   {"accountId",boost::json::value_from(accountId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AccountScript.OnFailedEmailChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        // Called when Password is successfully changed for Account
        void OnPasswordChange (uint32 accountId) override
        {
            try
            {
                boost::json::value jv = {
                   {"accountId",boost::json::value_from(accountId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AccountScript.OnPasswordChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }


        // Called when Password failed to change for Account
        void OnFailedPasswordChange (uint32 accountId) override
        {
            try
            {
                boost::json::value jv = {
                   {"accountId",boost::json::value_from(accountId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("AccountScript.OnFailedPasswordChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
                if (resp != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "% Produce failed: " <<
                        RdKafka::err2str(resp) << std::endl;
                }
                _producer->poll(0);
            }
            catch (...)
            {
            }
        }

    };
}
