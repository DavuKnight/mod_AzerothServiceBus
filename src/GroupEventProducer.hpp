
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
    class GroupEventProducer : public GroupScript
    {

    public:
        RdKafka::Producer* _producer;

        GroupEventProducer(RdKafka::Producer* producer) : GroupScript("GroupEventProducer") {
            _producer = producer;
        }

        // Called when a member is added to a group.
        void OnAddMember(Group* group, ObjectGuid guid) override{ }

        // Called when a member is invited to join a group.
        void OnInviteMember(Group* group, ObjectGuid guid)override { }

        // Called when a member is removed from a group.
        void OnRemoveMember(Group* group, ObjectGuid guid, RemoveMethod method, ObjectGuid kicker, const char* reason) override { }

        // Called when the leader of a group is changed.
        void OnChangeLeader(Group* group, ObjectGuid newLeaderGuid, ObjectGuid oldLeaderGuid) override { }

        // Called when a group is disbanded.
        void OnDisband(Group* group) override { }

        bool CanGroupJoinBattlegroundQueue(Group const* group, Player* member, Battleground const* bgTemplate, uint32 MinPlayerCount, bool isRated, uint32 arenaSlot) override { return true; }

        void OnCreate(Group* group, Player* leader) override { }

    };
}
