#include <memory/system/allocation/system_allocate.h>

#include <stdlib.h>
#ifndef SYNAPSE_BUILD_ENVIRONMENT_MSVC
#include <stdalign.h>
#endif

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
#ifdef SYNAPSE_BUILD_ENVIRONMENT_MSVC
    return 
        _aligned_malloc
            (pAllocSize, pAllocAlign);
#else
    return
        aligned_alloc
            (pAllocAlign, pAllocSize);
#endif
}

void
    synapse_memory_aligned_deallocate_from_system
        (void* pDealloc, size_t pDeallocSize)
{
#ifdef SYNAPSE_BUILD_ENVIRONMENT_MSVC
    _aligned_free
        (pDealloc);
#else
    free
        (pDealloc);
#endif
}