
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
    class GlobalEventProducer : public GlobalScript
    {

    public:
        RdKafka::Producer* _producer;

        GlobalEventProducer(RdKafka::Producer* producer) : GlobalScript("GlobalEventProducer") {
            _producer = producer;
        }
        //void OnItemDelFromDB(CharacterDatabaseTransaction trans, ObjectGuid::LowType itemGuid)override { }
        //void OnMirrorImageDisplayItem(Item const* item, uint32& display) override { }

        // loot
        //void OnAfterRefCount(Player const* player, LootStoreItem* LootStoreItem, Loot& loot, bool canRate, uint16 lootMode, uint32& maxcount, LootStore const& store) override { }
        //void OnBeforeDropAddItem(Player const* player, Loot& loot, bool canRate, uint16 lootMode, LootStoreItem* LootStoreItem, LootStore const& store) override { }
        //void OnInitializeLockedDungeons(Player* player, uint8& level, uint32& lockData, lfg::LFGDungeonData const* dungeon)override { }
        //void OnAfterInitializeLockedDungeons(Player* player)override { }

        // On Before arena points distribution
        //void OnBeforeUpdateArenaPoints(ArenaTeam* at, std::map<ObjectGuid, uint32>& ap) override { }

        // Called when a dungeon encounter is updated.
        //void OnAfterUpdateEncounterState(Map* map, EncounterCreditType type, uint32 creditEntry, Unit* source, Difficulty difficulty_fixed, DungeonEncounterList const* encounters, uint32 dungeonCompleted, bool updated)override { }

        // Called before the phase for a WorldObject is set
        //void OnBeforeWorldObjectSetPhaseMask(WorldObject const* worldObject, uint32& oldPhaseMask, uint32& newPhaseMask, bool& useCombinedPhases, bool& update)override { }

        // Called after loading spell dbc corrections
        //void OnLoadSpellCustomAttr(SpellInfo* spell) override { }


    };
}
