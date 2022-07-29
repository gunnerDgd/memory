#include <memory/system/allocation/system_page.h>
#include <Windows.h>

void*
    synapse_memory_allocate_page_from_system
        (void* pAllocHint, size_t pAllocPageCount)
{
    return
        VirtualAlloc
            (pAllocHint,
                pAllocPageCount * 4096,
                    MEM_COMMIT, PAGE_READWRITE);
}

void
    synapse_memory_deallocate_page_from_system
        (void* pDeallocPtr, size_t pDeallocSize)
{
    VirtualFree
        (pDeallocPtr, 0, MEM_FREE);
}

void
    synapse_memory_lock_page_from_system
        (void* pLockPtr, size_t pLockSize)
{
    return
        VirtualLock(pLockPtr, pLockSize);
}

void
    synapse_memory_unlock_page_from_system
        (void* pUnlockPtr, size_t pUnlockSize)
{
    return
        VirtualUnlock(pUnlockPtr, pUnlockSize);
}