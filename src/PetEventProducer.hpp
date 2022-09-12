
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
    class PetEventProducer : public PetScript
    {

    public:
        RdKafka::Producer* _producer;

        PetEventProducer(RdKafka::Producer* producer) : PetScript("PetEventProducer") {
            _producer = producer;
        }

        void OnInitStatsForLevel(Guardian* guardian, uint8 petlevel) override{ }

        void OnCalculateMaxTalentPointsForLevel(Pet* pet, uint8 level, uint8& points)override { }

        bool CanUnlearnSpellSet(Pet* pet, uint32 level, uint32 spell) override { return true; }

        bool CanUnlearnSpellDefault(Pet* pet, SpellInfo const* spellEntry)override { return true; }

        bool CanResetTalents(Pet* pet) override { return true; }

        /**
         * @brief This hook called after add pet in world
         *
         * @param pet Contains information about the Pet
         */
        void OnPetAddToWorld(Pet* pet)override { }
    };
}
