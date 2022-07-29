#include <memory/mman/nonpaged/details/mman_nonpaged_init.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>

#include <memory/system/allocation/system_allocate.h>

#include <Windows.h>

__synapse_memory_mman_nonpaged*
    __synapse_memory_mman_nonpaged_initialize
        ()
{
    __synapse_memory_mman_nonpaged*
        ptr_nonpaged
            = synapse_memory_allocate_from_system
                    (NULL, sizeof(__synapse_memory_mman_nonpaged));
    
    ZeroMemory
        (ptr_nonpaged,
            sizeof(__synapse_memory_mman_nonpaged_bucket));

    return
        ptr_nonpaged;
}

__synapse_memory_mman_nonpaged_page*
    __synapse_memory_mman_nonpaged_initialize_page
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    __synapse_memory_mman_nonpaged_page*
        ptr_bucket_page
            = synapse_memory_allocate_from_system
                (NULL, sizeof(__synapse_memory_mman_nonpaged_page));
    
    ptr_bucket_page->ptr_next
        = NULL;
    ptr_bucket_page->ptr_alloc_page
        = VirtualAlloc
                (NULL, __synapse_memory_mman_nonpaged_page_size,
                    MEM_COMMIT, PAGE_READWRITE);
    VirtualLock
        (ptr_bucket_page->ptr_alloc_page,
            __synapse_memory_mman_nonpaged_page_size);
    
    return
        ptr_bucket_page;
}

void
    __synapse_memory_mman_nonpaged_cleanup
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    while(pNonpaged->hnd_pooled_page)
    {
        __synapse_memory_mman_nonpaged_page*
            ptr_dealloc
                = pNonpaged->hnd_pooled_page;

        pNonpaged->hnd_pooled_page
            = ptr_dealloc->ptr_next;

        __synapse_memory_mman_nonpaged_cleanup_page
            (ptr_dealloc);
    }
}

void
    __synapse_memory_mman_nonpaged_cleanup_page
        (__synapse_memory_mman_nonpaged_page* pBucketPage)
{
    VirtualUnlock
        (pBucketPage->ptr_alloc_page, 
            __synapse_memory_mman_nonpaged_page_size);
    VirtualFree
        (pBucketPage->ptr_alloc_page, 0, MEM_FREE);

    synapse_memory_deallocate_from_system
        (pBucketPage, sizeof(__synapse_memory_mman_nonpaged_page));
}