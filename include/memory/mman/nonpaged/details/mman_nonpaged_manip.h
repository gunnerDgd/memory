#include <memory/mman/nonpaged/details/mman_nonpaged_type.h>

void*
    __synapse_memory_mman_nonpaged_allocate
        (__synapse_memory_mman_nonpaged*, size_t);

void
    __synapse_memory_mman_nonpaged_deallocate
        (__synapse_memory_mman_nonpaged*, __synapse_memory_mman_nonpaged_bucket*);

void
    __synapse_memory_mman_nonpaged_reserve_page
        (__synapse_memory_mman_nonpaged*, __synapse_memory_mman_nonpaged_page*);

void
    __synapse_memory_mman_nonpaged_reserve
        (__synapse_memory_mman_nonpaged*, uint8_t);