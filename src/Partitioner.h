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
 /* Use of this partitioner is pretty pointless since no key is provided
  * in the produce() call. */
class Partitioner : public RdKafka::PartitionerCb
{
public:
    int32_t partitioner_cb(const RdKafka::Topic* topic, const std::string* key,
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
