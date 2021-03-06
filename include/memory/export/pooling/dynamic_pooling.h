#include <memory/defines/export/export.h>
#include <memory/interface/memory_pooling.h>

synapse_memory_dll
    synapse_memory_dynamic_pool*
        synapse_initialize_dynamic_pool
            (size_t, size_t);

synapse_memory_dll
    void
        synapse_cleanup_dynamic_pool
            (synapse_memory_dynamic_pool*);