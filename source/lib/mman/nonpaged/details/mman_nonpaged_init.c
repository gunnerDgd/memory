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
        (ptr_nonpaged->hnd_pooled, 
            sizeof(__synapse_memory_mman_nonpaged_bucket*)
                * __synapse_nonpaged_bucket_count);
    ZeroMemory
        (ptr_nonpaged->hnd_pooled_page, 
            sizeof(__synapse_memory_mman_nonpaged_bucket*)
                * __synapse_nonpaged_bucket_count);

    return
        ptr_nonpaged;
}

__synapse_memory_mman_nonpaged_bucket*
    __synapse_memory_mman_nonpaged_initialize_bucket
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    __synapse_memory_mman_nonpaged_bucket*
        ptr_bucket
            = synapse_memory_allocate_from_system
                    (NULL, sizeof(__synapse_memory_mman_nonpaged_bucket));
    
    ptr_bucket->ptr_next
        = NULL;
    ptr_bucket->ptr_parent_pool
        = pNonpaged;
    return
        ptr_bucket;
}

__synapse_memory_mman_nonpaged_bucket_page*
    __synapse_memory_mman_nonpaged_initialize_bucket_page
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    __synapse_memory_mman_nonpaged_bucket_page*
        ptr_bucket_page
            = synapse_memory_allocate_from_system
                (NULL, sizeof(__synapse_memory_mman_nonpaged_bucket_page));
    
    ptr_bucket_page->ptr_next
        = NULL;
    ptr_bucket_page->ptr_page
        = VirtualAlloc
                (NULL, __synapse_nonpaged_bucket_page_size,
                    MEM_COMMIT, PAGE_READWRITE);
    VirtualLock
        (ptr_bucket_page->ptr_page,
            __synapse_nonpaged_bucket_page_size);
    
    return
        ptr_bucket_page;
}

void
    __synapse_memory_mman_nonpaged_cleanup
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    __synapse_memory_mman_nonpaged_bucket_page*
        ptr_bucket_page
            = pNonpaged->hnd_pooled_page;
    __synapse_memory_mman_nonpaged_bucket*
        ptr_bucket
            = pNonpaged->hnd_pooled;

    while(ptr_bucket_page)
    {
        __synapse_memory_mman_nonpaged_bucket_page*
            ptr_dealloc_next
                = ptr_bucket_page->ptr_next;
        
        __synapse_memory_mman_nonpaged_cleanup_bucket_page
            (ptr_bucket_page);
        ptr_bucket_page
            = ptr_dealloc_next;
    }

    for (uint8_t it_index = 0;
                 it_index < 5;
                 it_index++)
    {
        ptr_bucket
            = pNonpaged->hnd_pooled[it_index];
        while(ptr_bucket)
        {
            __synapse_memory_mman_nonpaged_bucket*
                ptr_dealloc_next
                    = ptr_bucket->ptr_next;
            
            __synapse_memory_mman_nonpaged_cleanup_bucket
                (ptr_bucket);
            
            ptr_bucket
                = ptr_dealloc_next;
        }
    }
}

void
    __synapse_memory_mman_nonpaged_cleanup_bucket
        (__synapse_memory_mman_nonpaged_bucket* pBucket)
{
    synapse_memory_deallocate_from_system
        (pBucket, sizeof(__synapse_memory_mman_nonpaged_bucket));
}

void
    __synapse_memory_mman_nonpaged_cleanup_bucket_page
        (__synapse_memory_mman_nonpaged_bucket_page* pBucketPage)
{
    VirtualUnlock
        (pBucketPage->ptr_page, __synapse_nonpaged_bucket_page_size);
    VirtualFree
        (pBucketPage->ptr_page, 0, MEM_FREE);

    synapse_memory_deallocate_from_system
        (pBucketPage, sizeof(__synapse_memory_mman_nonpaged_bucket_page));
}