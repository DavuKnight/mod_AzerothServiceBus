
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
    class GuildEventProducer : public GuildScript
    {

    public:
        RdKafka::Producer* _producer;

        GuildEventProducer(RdKafka::Producer* producer) : GuildScript("GuildEventProducer") {
            _producer = producer;
        }
        // Called when a member is added to the guild.
        void OnAddMember(Guild* guild, Player* player, uint8& plRank) override { }

        // Called when a member is removed from the guild.
        void OnRemoveMember(Guild* guild, Player* player, bool isDisbanding, bool isKicked) override { }

        // Called when the guild MOTD (message of the day) changes.
        void OnMOTDChanged(Guild* guild, const std::string& newMotd) override { }

        // Called when the guild info is altered.
        void OnInfoChanged(Guild* guild, const std::string& newInfo) override { }

        // Called when a guild is created.
        void OnCreate(Guild* guild, Player* leader, const std::string& name) override { }

        // Called when a guild is disbanded.
        void OnDisband(Guild* guild) override { }

        // Called when a guild member withdraws money from a guild bank.
        void OnMemberWitdrawMoney(Guild* guild, Player* player, uint32& amount, bool isRepair) override { }

        // Called when a guild member deposits money in a guild bank.
        void OnMemberDepositMoney(Guild* guild, Player* player, uint32& amount) override { }

        // Called when a guild member moves an item in a guild bank.
        void OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
            bool isDestBank, uint8 destContainer, uint8 destSlotId) override { }

        void OnEvent(Guild* guild, uint8 eventType, ObjectGuid::LowType playerGuid1, ObjectGuid::LowType playerGuid2, uint8 newRank) override { }

        void OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, ObjectGuid::LowType playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId) override{ }

    };
}
