#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>

#if _AIX
#include <unistd.h>
#endif

#include "../deps/librdkafka-1.8.2/src-cpp/rdkafkacpp.h"

class DeliveryReport : public RdKafka::DeliveryReportCb {
public:
    void dr_cb(RdKafka::Message& message) {
        /* If message.err() is non-zero the message delivery failed permanently
         * for the message. */
        if (message.err())
            std::cerr << "% Message delivery failed: " << message.errstr() << std::endl;
        else
            std::cerr << "% Message delivered to topic " << message.topic_name() <<
            " [" << message.partition() << "] at offset " <<
            message.offset() << std::endl;
    }
};
