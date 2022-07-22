#include <stdint.h>
#include <stddef.h>

void*
    synapse_memory_allocate_from_system
        (void*, size_t);

void
    synapse_memory_deallocate_from_system
        (void*, size_t);