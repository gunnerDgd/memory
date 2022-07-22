#include <memory/mman/nonpaged/details/mman_nonpaged_type.h>

__synapse_memory_mman_nonpaged*
    __synapse_memory_mman_nonpaged_initialize
        ();

__synapse_memory_mman_nonpaged_bucket*
    __synapse_memory_mman_nonpaged_initialize_bucket
        (__synapse_memory_mman_nonpaged*);

__synapse_memory_mman_nonpaged_bucket_page*
    __synapse_memory_mman_nonpaged_initialize_bucket_page
        (__synapse_memory_mman_nonpaged*);

void
    __synapse_memory_mman_nonpaged_cleanup
        (__synapse_memory_mman_nonpaged*);

void
    __synapse_memory_mman_nonpaged_cleanup_bucket
        (__synapse_memory_mman_nonpaged_bucket*);

void
    __synapse_memory_mman_nonpaged_cleanup_bucket_page
        (__synapse_memory_mman_nonpaged_bucket_page*);
