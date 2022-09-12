
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
        void OnAddMember(Group* group, ObjectGuid guid) override
        {
            try
            {
                boost::json::value jv = {
                    {"group",boost::json::value_from(group) },
                    {"guid",boost::json::value_from(guid) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GroupScript.OnAddMember", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a member is invited to join a group.
        void OnInviteMember(Group* group, ObjectGuid guid)override
        {
            try
            {
                boost::json::value jv = {
                    {"group",boost::json::value_from(group) },
                    {"guid",boost::json::value_from(guid) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GroupScript.OnInviteMember", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a member is removed from a group.
        void OnRemoveMember(Group* group, ObjectGuid guid, RemoveMethod method, ObjectGuid kicker, const char* reason) override
        {
            try
            {
                boost::json::value jv = {
                    {"group",boost::json::value_from(group) },
                    {"guid",boost::json::value_from(guid) },
                    {"method",boost::json::value_from(method) },
                    {"kicker",boost::json::value_from(kicker) },
                    {"reason",reason }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GroupScript.OnRemoveMember", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        // Called when the leader of a group is changed.
        void OnChangeLeader(Group* group, ObjectGuid newLeaderGuid, ObjectGuid oldLeaderGuid) override
        {
            try
            {
                boost::json::value jv = {
                    {"group",boost::json::value_from(group) },
                    {"newLeaderGuid",boost::json::value_from(newLeaderGuid) },
                    {"oldLeaderGuid",boost::json::value_from(oldLeaderGuid) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GroupScript.OnChangeLeader", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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

        // Called when a group is disbanded.
        void OnDisband(Group* group) override
        {
            try
            {
                boost::json::value jv = {
                    {"group",boost::json::value_from(group) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GroupScript.OnDisband", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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


        void OnCreate(Group* group, Player* leader) override
        {
            try
            {
                boost::json::value jv = {
                    {"group",boost::json::value_from(group) },
                    {"leader",boost::json::value_from(leader) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("GroupScript.OnCreate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
