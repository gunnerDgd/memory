#include <memory/interface/memory_pooling.h>
#include <memory/defines/export/export.h>

synapse_memory_dll
    synapse_memory_static_pool*
        synapse_initialize_static_pool
            (size_t, size_t);

synapse_memory_dll
    void
        synapse_cleanup_static_pool
            (synapse_memory_static_pool*);