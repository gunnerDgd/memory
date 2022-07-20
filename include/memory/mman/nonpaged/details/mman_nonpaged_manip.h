#include <memory/mman/nonpaged/details/mman_nonpaged_type.h>

__synapse_memory_mman_nonpaged_block*
    __synapse_memory_mman_nonpaged_allocate
        (__synapse_memory_mman_nonpaged*);

void
    __synapse_memory_mman_nonpaged_deallocate
        (__synapse_memory_mman_nonpaged*, __synapse_memory_mman_nonpaged_block*);

void
    __synapse_memory_mman_nonpaged_deallocate_all
        (__synapse_memory_mman_nonpaged*);

void
    __synapse_memory_mman_nonpaged_reserve
        (__synapse_memory_mman_nonpaged*, size_t);