
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
    class MiscEventProducer : public MiscScript
    {

    public:
        RdKafka::Producer* _producer;

        MiscEventProducer(RdKafka::Producer* producer) : MiscScript("MiscEventProducer") {
            _producer = producer;
        }

        void OnConstructObject(Object* origin) override { }

        void OnDestructObject(Object* origin) override { }

        void OnConstructPlayer(Player* origin) override { }

        void OnDestructPlayer(Player* origin) override { }

        void OnConstructGroup(Group* origin) override { }

        void OnDestructGroup(Group* origin) override { }

        void OnConstructInstanceSave(InstanceSave* origin) override { }

        void OnDestructInstanceSave(InstanceSave* origin) override { }

        void OnItemCreate(Item* item, ItemTemplate const* itemProto, Player const* owner)override { }

        void OnAfterLootTemplateProcess(Loot* loot, LootTemplate const* tab, LootStore const& store, Player* lootOwner, bool personal, bool noEmptyError, uint16 lootMode) override { }

        void OnPlayerSetPhase(const AuraEffect* auraEff, AuraApplication const* aurApp, uint8 mode, bool apply, uint32& newPhase) override { }

        void OnInstanceSave(InstanceSave* instanceSave) override { }

    };
}
