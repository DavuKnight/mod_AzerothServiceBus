
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

        void OnConstructObject(Object* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnConstructObject", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnDestructObject(Object* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnDestructObject", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnConstructPlayer(Player* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnConstructPlayer", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnDestructPlayer(Player* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnDestructPlayer", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnConstructGroup(Group* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnConstructGroup", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnDestructGroup(Group* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnDestructGroup", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnConstructInstanceSave(InstanceSave* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnConstructInstanceSave", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnDestructInstanceSave(InstanceSave* origin) override
        {
            try
            {
                boost::json::value jv = {
                    {"origin",boost::json::value_from(origin) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnDestructInstanceSave", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnItemCreate(Item* item, ItemTemplate const* itemProto, Player const* owner)override
        {
            try
            {
                boost::json::value jv = {
                    {"item",boost::json::value_from(item) },
                    {"itemProto",boost::json::value_from(itemProto) },
                    {"owner",boost::json::value_from(owner) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnItemCreate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnAfterLootTemplateProcess(Loot* loot, LootTemplate const* tab, LootStore const& store, Player* lootOwner, bool personal, bool noEmptyError, uint16 lootMode) override
        {
            try
            {
                boost::json::value jv = {
                    {"loot",boost::json::value_from(loot) },
                    //{"tab",boost::json::value_from(tab) },
                    //{"store",boost::json::value_from(store) },
                    {"lootOwner",boost::json::value_from(lootOwner) },
                    {"personal",boost::json::value_from(personal) },
                    {"noEmptyError",boost::json::value_from(noEmptyError) },
                    {"lootMode",boost::json::value_from(lootMode) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnAfterLootTemplateProcess", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnPlayerSetPhase(const AuraEffect* auraEff, AuraApplication const* aurApp, uint8 mode, bool apply, uint32& newPhase) override
        {
            try
            {
                boost::json::value jv = {
                    {"player",boost::json::value_from(auraEff) },
                    {"Item",boost::json::value_from(aurApp) },
                    {"bag",boost::json::value_from(mode) },
                    {"slot",boost::json::value_from(apply) },
                    {"update",boost::json::value_from(newPhase) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MiscScript.OnPlayerSetPhase", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
