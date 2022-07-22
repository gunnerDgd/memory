#include <memory/system_specific/allocate.h>
#include <stdlib.h>

void*
    synapse_memory_allocate_from_system
        (void* pAllocHint, size_t pAllocSize)
{
    return
        malloc(pAllocSize);
}

void
    synapse_memory_deallocate_from_system
        (void* pDealloc, size_t pDeallocSize)
{
    free(pDealloc);
}