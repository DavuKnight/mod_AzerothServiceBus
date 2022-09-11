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
    class PlayerEventProducer : public PlayerScript
    {
    public:
        RdKafka::Producer* _producer;
        RdKafka::Producer* _producer;
        void OnAchiComplete(Player* player, AchievementEntry const* achievement) override;
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) override;
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel) override;
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group) override;
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild) override;
        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Player* receiver) override;
        void OnCreate(Player* player) override;
        void OnFirstLogin(Player* player) override;
        void OnLogin(Player* player) override;
        void OnLogout(Player* player) override;
    };
}
