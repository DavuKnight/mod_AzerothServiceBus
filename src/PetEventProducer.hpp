
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

        /**
         * @brief This hook called after add pet in world
         *
         * @param pet Contains information about the Pet
         */
        void OnPetAddToWorld(Pet* pet)override
        {
            try
            {
                boost::json::value jv = {
                    {"pet",boost::json::value_from(pet) }
                };
                std::string body = serialize(jv);

                RdKafka::ErrorCode resp = _producer->produce("PetScript.OnPetAddToWorld", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
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
