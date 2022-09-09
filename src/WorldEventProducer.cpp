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

#if _AIX
#include <unistd.h>
#endif

 /*
  * Typical include path in a real application would be
  * #include <librdkafka/rdkafkacpp.h>
  */
#include "../deps/librdkafka-1.8.2/src-cpp/rdkafkacpp.h"
  // Add player scripts
class WorldEventProducer : public WorldScript
{
public:
    RdKafka::Producer* _producer;

    WorldEventProducer(RdKafka::Producer* producer) : WorldScript("WorldEventProducer") {
        _producer = producer;

    }
    void OnAfterConfigLoad(bool reload) override
    {
        std::string body = "";
        _producer->produce("World:OnAfterConfigLoad", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnAfterUnloadAllMaps()override
    {
        std::string body = "";
        _producer->produce("World:OnAfterUnloadAllMaps", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnBeforeConfigLoad(bool reload) override
    {
        std::string body = "";
        _producer->produce("World:OnBeforeConfigLoad", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnBeforeFinalizePlayerWorldSession(uint32& cacheversion) override
    {
        std::string body = "";
        _producer->produce("World:OnBeforeFinalizePlayerWorldSession", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnBeforeWorldInitialized() override
    {
        std::string body = "";
        _producer->produce("World:OnBeforeWorldInitialized", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }
    void OnLoadCustomDatabaseTable() override
    {
        std::string body = "";
        _producer->produce("World:OnLoadCustomDatabaseTable", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }
    void OnMotdChange(std::string& newMotd) override
    {
        std::string body = "";
        _producer->produce("World:OnMotdChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnOpenStateChange(bool open) override
    {
        std::string body = "";
        _producer->produce("World:OnOpenStateChange", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }
    
    void OnShutdown() override
    {
        std::string body = "";
        _producer->produce("World:OnShutdown", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnShutdownCancel() override
    {
        std::string body = "";
        _producer->produce("World:OnShutdownCancel", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }
    void OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask) override
    {
        std::string body = "";
        _producer->produce("World:OnShutdownInitiate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnStartup() override
    {
        std::string body = "";
        _producer->produce("World:OnStartup", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);

    }

    void OnUpdate(uint32 diff) override
    {
        _producer->poll(0);
    }
};
