#include <memory/mman/nonpaged/details/mman_nonpaged_type.h>

__synapse_memory_mman_nonpaged*
    __synapse_memory_mman_nonpaged_initialize
        ();

__synapse_memory_mman_nonpaged_page*
    __synapse_memory_mman_nonpaged_initialize_page
        (__synapse_memory_mman_nonpaged*);

void
    __synapse_memory_mman_nonpaged_cleanup
        (__synapse_memory_mman_nonpaged*);

void
    __synapse_memory_mman_nonpaged_cleanup_page
        (__synapse_memory_mman_nonpaged_page*);
