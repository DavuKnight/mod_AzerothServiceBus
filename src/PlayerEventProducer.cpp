/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

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

#if _AIX
#include <unistd.h>
#endif

 /*
  * Typical include path in a real application would be
  * #include <librdkafka/rdkafkacpp.h>
  */
#include "../deps/librdkafka-1.8.2/src-cpp/rdkafkacpp.h"
// Add player scripts
class PlayerEventProducer : public PlayerScript
{

public:
    RdKafka::Producer* _producer;

    PlayerEventProducer(RdKafka::Producer* producer) : PlayerScript("PlayerEventProducer") {
        _producer = producer;
    }

    void OnLogin(Player* player) override
    {
        std::string body = "test";
        _producer->produce("Player:OnLogin",RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY,  const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
        //_producer->produce(
        //    /* Topic name */
        //    topic,
        //    /* Any Partition: the builtin partitioner will be
        //     * used to assign the message to a topic based
        //     * on the message key, or random partition if
        //     * the key is not set. */
        //    RdKafka::Topic::PARTITION_UA,
        //    /* Make a copy of the value */
        //    RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
        //    /* Value */
        //    const_cast<char*>(body.c_str()), body.size(),
        //    /* Key */
        //    NULL, 0,
        //    /* Timestamp (defaults to current time) */
        //    0,
        //    /* Message headers, if any */
        //    NULL,
        //    /* Per-message opaque value passed to
        //     * delivery report */
        //    NULL);

        //if (err != RdKafka::ERR_NO_ERROR) {
        //    std::cerr << "% Failed to produce to topic " << topic << ": " <<
        //        RdKafka::err2str(err) << std::endl;

        //    if (err == RdKafka::ERR__QUEUE_FULL) {
        //        /* If the internal queue is full, wait for
        //         * messages to be delivered and then retry.
        //         * The internal queue represents both
        //         * messages to be sent and messages that have
        //         * been sent or failed, awaiting their
        //         * delivery report callback to be called.
        //         *
        //         * The internal queue is limited by the
        //         * configuration property
        //         * queue.buffering.max.messages */
        //        _producer->poll(1000/*block for max 1000ms*/);
        //        goto retry;
        //    }

        //}
        //else {
        //    std::cerr << "% Enqueued message (" << body.size() << " bytes) " <<
        //        "for topic " << topic << std::endl;
        //}
    }
};




