#include <memory/interface/memory_manager.h>

synapse_memory_block
    synapse_memory_mman_nonpaged_allocate
        (synapse_memory_manager_handle, void*, size_t);

void
    synapse_memory_mman_nonpaged_deallocate
        (synapse_memory_manager_handle, synapse_memory_block);

void
    synapse_memory_mman_nonpaged_deallocate_all
        (synapse_memory_manager_handle);

void*
    synapse_memory_mman_nonpaged_block_pointer
        (synapse_memory_block);

size_t
    synapse_memory_mman_nonpaged_block_size
        (synapse_memory_block);