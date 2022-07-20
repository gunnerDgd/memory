#include <memory/interface/memory_manager.h>

synapse_memory_manager_handle
    synapse_memory_mman_nonpaged_initialize
        (size_t);

void
    synapse_memory_mman_nonpaged_cleanup
        (synapse_memory_manager_handle);