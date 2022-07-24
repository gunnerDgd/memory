#include <memory/system/allocation/system_allocate.h>

#include <stdlib.h>
#include <stdalign.h>

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

void*
    synapse_memory_aligned_allocate_from_system
        (void* pAllocHint, size_t pAllocSize, size_t pAllocAlign)
{
    return 
        _aligned_malloc
            (pAllocSize, pAllocAlign);
}

void
    synapse_memory_aligned_deallocate_from_system
        (void* pDealloc, size_t pDeallocSize)
{
    _aligned_free
        (pDealloc);
}