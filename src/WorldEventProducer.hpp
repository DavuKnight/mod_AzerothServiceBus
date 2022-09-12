/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

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
#include "../deps/librdkafka-1.8.2/src-cpp/rdkafkacpp.h"
#if _AIX
#include <unistd.h>
#endif
#include "Serialization/Templates.h"
 /*
  * Typical include path in a real application would be
  * #include <librdkafka/rdkafkacpp.h>
  */
#include "../deps/librdkafka-1.8.2/src-cpp/rdkafkacpp.h"


static volatile sig_atomic_t run = 1;

static void sigterm(int sig) {
    run = 0;
}
  // Add player scripts
namespace mod_AzerothServiceBus
{
    class WorldEventProducer : public WorldScript
    {
    public:
        RdKafka::Producer* _producer;

        WorldEventProducer(RdKafka::Producer* producer) : WorldScript("WorldEventProducer") {
            _producer = producer;
        }

        void OnBeforeConfigLoad(bool reload) override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnBeforeConfigLoad", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        void OnAfterConfigLoad(bool reload) override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnAfterConfigLoad", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnAfterUnloadAllMaps()override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnAfterUnloadAllMaps", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnBeforeFinalizePlayerWorldSession(uint32& cacheversion) override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnBeforeFinalizePlayerWorldSession", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnBeforeWorldInitialized() override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnBeforeWorldInitialized", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        void OnLoadCustomDatabaseTable() override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnLoadCustomDatabaseTable", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        void OnMotdChange(std::string& newMotd) override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnMotdChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnOpenStateChange(bool open) override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnOpenStateChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnShutdown() override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnShutdown", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnShutdownCancel() override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnShutdownCancel", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
        void OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask) override
        {
            try
            {
                std::string body = "";
                RdKafka::ErrorCode resp = _producer->produce("WorldScript.OnShutdownInitiate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnStartup() override
        {
            try
            {
                _producer->flush(0);
            }
            catch (...)
            {
            }
        }

        void OnUpdate(uint32 diff) override
        {
            _producer->poll(0);
        }
    };
}
