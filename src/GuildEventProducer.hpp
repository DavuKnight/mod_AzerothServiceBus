
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
        void OnAddMember(Guild* guild, Player* player, uint8& plRank) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"player",boost::json::value_from(player) },
                    {"plRank",boost::json::value_from(plRank) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a member is removed from the guild.
        void OnRemoveMember(Guild* guild, Player* player, bool isDisbanding, bool isKicked) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"player",boost::json::value_from(player) },
                    {"isDisbanding",boost::json::value_from(isDisbanding) },
                    {"isKicked",boost::json::value_from(isKicked) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when the guild MOTD (message of the day) changes.
        void OnMOTDChanged(Guild* guild, const std::string& newMotd) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"newMotd",boost::json::value_from(newMotd) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when the guild info is altered.
        void OnInfoChanged(Guild* guild, const std::string& newInfo) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"newInfo",boost::json::value_from(newInfo) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a guild is created.
        void OnCreate(Guild* guild, Player* leader, const std::string& name) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"leader",boost::json::value_from(leader) },
                    {"name",boost::json::value_from(name) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a guild is disbanded.
        void OnDisband(Guild* guild) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a guild member withdraws money from a guild bank.
        void OnMemberWitdrawMoney(Guild* guild, Player* player, uint32& amount, bool isRepair) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"player",boost::json::value_from(player) },
                    {"amount",boost::json::value_from(amount) },
                    {"isRepair",boost::json::value_from(isRepair) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a guild member deposits money in a guild bank.
        void OnMemberDepositMoney(Guild* guild, Player* player, uint32& amount) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"player",boost::json::value_from(player) },
                    {"amount",boost::json::value_from(amount) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a guild member moves an item in a guild bank.
        void OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
            bool isDestBank, uint8 destContainer, uint8 destSlotId) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"player",boost::json::value_from(player) },
                    {"pItem",boost::json::value_from(pItem) },
                    {"isSrcBank",boost::json::value_from(isSrcBank) },
                    {"srcContainer",boost::json::value_from(srcContainer) },
                    {"srcSlotId",boost::json::value_from(srcSlotId) },
                    {"isDestBank",boost::json::value_from(isDestBank) },
                    {"destContainer",boost::json::value_from(destContainer) },
                    {"destSlotId",boost::json::value_from(destSlotId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnEvent(Guild* guild, uint8 eventType, ObjectGuid::LowType playerGuid1, ObjectGuid::LowType playerGuid2, uint8 newRank) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"eventType",boost::json::value_from(eventType) },
                    {"playerGuid1",boost::json::value_from(playerGuid1) },
                    {"playerGuid2",boost::json::value_from(playerGuid2) },
                    {"newRank",boost::json::value_from(newRank) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        void OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, ObjectGuid::LowType playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId) override
        {
            try
            {
                boost::json::value jv = {
                    {"guild",boost::json::value_from(guild) },
                    {"eventType",boost::json::value_from(eventType) },
                    {"tabId",boost::json::value_from(tabId) },
                    {"playerGuid",boost::json::value_from(playerGuid) },
                    {"itemOrMoney",boost::json::value_from(itemOrMoney) },
                    {"itemStackCount",boost::json::value_from(itemStackCount) },
                    {"destTabId",boost::json::value_from(destTabId) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PlayerScript.OnAfterMoveItemFromInventory", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
