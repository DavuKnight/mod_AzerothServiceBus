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
#include "PlayerEventProducer.cpp"
#include "WorldEventProducer.cpp"
using namespace RdKafka;


static volatile sig_atomic_t run = 1;

static void sigterm(int sig) {
    run = 0;
}
class ExampleDeliveryReportCb : public RdKafka::DeliveryReportCb {
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
// From SC
void AddMyEventScripts(RdKafka::Producer*);

// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void Addmod_AzerothServiceBusScripts()
{

    std::string Server = "127.0.0.1";


    /*
     * Create configuration object
     */
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    std::string errstr;

    /* Set bootstrap broker(s) as a comma-separated list of
     * host or host:port (default port 9092).
     * librdkafka will use the bootstrap brokers to acquire the full
     * set of brokers from the cluster. */
    if (conf->set("bootstrap.servers", Server, errstr) !=
        RdKafka::Conf::CONF_OK) {
        std::cerr << errstr << std::endl;
        exit(1);
    }

    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);

    /* Set the delivery report callback.
     * This callback will be called once per message to inform
     * the application if delivery succeeded or failed.
     * See dr_msg_cb() above.
     * The callback is only triggered from ::poll() and ::flush().
     *
     * IMPORTANT:
     * Make sure the DeliveryReport instance outlives the Producer object,
     * either by putting it on the heap or as in this case as a stack variable
     * that will NOT go out of scope for the duration of the Producer object.
     */
    ExampleDeliveryReportCb ex_dr_cb;

    if (conf->set("dr_cb", &ex_dr_cb, errstr) != RdKafka::Conf::CONF_OK) {
        std::cerr << errstr << std::endl;
        exit(1);
    }

    /*
     * Create producer instance.
     */
    RdKafka::Producer* producer = RdKafka::Producer::create(conf, errstr);
    if (!producer) {
        std::cerr << "Failed to create producer: " << errstr << std::endl;
        exit(1);
    }

    delete conf;

    AddMyEventScripts(producer);


}
void AddMyEventScripts(RdKafka::Producer* producer)
{
    new PlayerEventProducer(producer);
    new WorldEventProducer(producer);

}

/* Use of this partitioner is pretty pointless since no key is provided
 * in the produce() call. */
class MyHashPartitionerCb : public PartitionerCb
{
public:
    int32_t partitioner_cb(const Topic* topic, const std::string* key,
        int32_t partition_cnt, void* msg_opaque) {
        return djb_hash(key->c_str(), key->size()) % partition_cnt;
    }
private:

    static inline unsigned int djb_hash(const char* str, size_t len) {
        unsigned int hash = 5381;
        for (size_t i = 0; i < len; i++)
            hash = ((hash << 5) + hash) + str[i];
        return hash;
    }
};

