
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
    class MailEventProducer : public MailScript
    {

    public:
        RdKafka::Producer* _producer;

        MailEventProducer(RdKafka::Producer* producer) : MailScript("MailEventProducer") {
            _producer = producer;
        }
        virtual void OnBeforeMailDraftSendMailTo(MailDraft* mailDraft, MailReceiver const& receiver, MailSender const& sender, MailCheckMask& checked,
            uint32& deliver_delay, uint32& custom_expiration, bool& deleteMailItemsFromDB, bool& sendMail)
        {
            try
            {
                boost::json::value jv = {
                    {"mailDraft",boost::json::value_from(mailDraft) },
                    {"receiver",boost::json::value_from(receiver) },
                    {"sender",boost::json::value_from(sender) },
                    {"checked",boost::json::value_from(checked) },
                    {"deliver_delay",boost::json::value_from(deliver_delay) },
                    {"custom_expiration",boost::json::value_from(custom_expiration) },
                    {"deleteMailItemsFromDB",boost::json::value_from(deleteMailItemsFromDB) },
                    {"sendMail",boost::json::value_from(sendMail) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("MapScript.OnCreate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
