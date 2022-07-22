#include <memory/mman/nonpaged/details/mman_nonpaged_type.h>

__synapse_memory_mman_nonpaged_bucket*
    __synapse_memory_mman_nonpaged_allocate
        (__synapse_memory_mman_nonpaged*, size_t);

void
    __synapse_memory_mman_nonpaged_allocate_bucket_page
        (__synapse_memory_mman_nonpaged*, __synapse_memory_mman_nonpaged_bucket_page*);

void
    __synapse_memory_mman_nonpaged_allocate_bucket
        (__synapse_memory_mman_nonpaged*, __synapse_memory_mman_nonpaged_bucket*, void*, uint8_t);

void
    __synapse_memory_mman_nonpaged_deallocate
        (__synapse_memory_mman_nonpaged*, __synapse_memory_mman_nonpaged_bucket*);

void
    __synapse_memory_mman_nonpaged_reserve
        (__synapse_memory_mman_nonpaged*, uint8_t);