#include <stdint.h>
#include <stddef.h>

void*
    synapse_memory_allocate_page_from_system
        (void*, size_t);

void
    synapse_memory_deallocate_page_from_system
        (void*, size_t);

void
    synapse_memory_lock_page_from_system
        (void*, size_t);

void
    synapse_memory_unlock_page_from_system
        (void*, size_t);