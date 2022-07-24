#include <memory/mman/nonpaged/details/mman_nonpaged_init.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>

#include <Windows.h>

__synapse_memory_mman_nonpaged_bucket*
    __synapse_memory_mman_nonpaged_allocate
        (__synapse_memory_mman_nonpaged* pNonpaged, size_t pAllocRound)
{
    __synapse_memory_mman_nonpaged_bucket*
        ptr_mblock 
            = NULL;

    do
    {
        ptr_mblock
            = pNonpaged->hnd_pooled[pAllocRound];
        
        if(!ptr_mblock)
            return NULL;
    } while
        (ptr_mblock
            != InterlockedCompareExchange64
                    (&pNonpaged->hnd_pooled[pAllocRound],
                        ptr_mblock->ptr_next, ptr_mblock));

    return
        ptr_mblock;
}

void
    __synapse_memory_mman_nonpaged_allocate_bucket_page
        (__synapse_memory_mman_nonpaged*             pNonpaged,
         __synapse_memory_mman_nonpaged_bucket_page* pNonpagedPage)
{

__try_first_allocate_page:
    if(InterlockedCompareExchange64
            (&pNonpaged->hnd_pooled_page,
                pNonpagedPage, 0))
                    goto __try_allocate_page;
    else
        return;
__try_allocate_page:
    do
    {
        pNonpagedPage->ptr_next
            = pNonpaged->hnd_pooled;
    } while
        (pNonpaged->hnd_pooled
            != InterlockedCompareExchange64
                    (&pNonpaged->hnd_pooled, pNonpagedPage,
                        pNonpaged->hnd_pooled_page));
}

void
    __synapse_memory_mman_nonpaged_allocate_bucket
        (__synapse_memory_mman_nonpaged*        pNonpaged, 
         __synapse_memory_mman_nonpaged_bucket* pBucket, 
         void*                                  pNonpagedPtr,
         uint8_t                                pNonpagedIndex)
{
    __synapse_memory_mman_nonpaged_bucket*
        ptr_bucket
            = __synapse_memory_mman_nonpaged_initialize_bucket
                    (pNonpaged);
    
    ptr_bucket->ptr_nonpaged
        = pNonpagedPtr;
    
__try_first_allocate:
    if(InterlockedCompareExchange64
            (&pNonpaged->hnd_pooled[pNonpagedIndex], 
                ptr_bucket, 0))
                    goto __try_allocate;
    else
        return;

__try_allocate:
    do
    {
        ptr_bucket->ptr_next
            = pNonpaged->hnd_pooled[pNonpagedIndex];
    } while
        (ptr_bucket
            != InterlockedCompareExchange64
                    (&pNonpaged->hnd_pooled[pNonpagedIndex], ptr_bucket,
                        pNonpaged->hnd_pooled));
    
    return;
}

void
    __synapse_memory_mman_nonpaged_deallocate
        (__synapse_memory_mman_nonpaged*        pNonpaged,
         __synapse_memory_mman_nonpaged_bucket* pNonpagedBlock)
{
    __synapse_memory_mman_nonpaged_bucket*
        ptr_bucket;
    if(pNonpagedBlock->ptr_parent_pool
            != pNonpaged)
                    return;

__try_first_deallocate:
    if(InterlockedCompareExchange64
            (&pNonpaged->hnd_pooled,
                pNonpagedBlock, NULL))
                    goto __try_deallocate;
    else
        return;
__try_deallocate:
    do
    {
        ptr_bucket
            = pNonpaged->hnd_pooled;
        pNonpagedBlock->ptr_next
            = ptr_bucket;
    } while
        (ptr_bucket
            != InterlockedCompareExchange64
                    (&pNonpaged->hnd_pooled,
                        pNonpagedBlock, ptr_bucket));

    return;
}

void
    __synapse_memory_mman_nonpaged_reserve
        (__synapse_memory_mman_nonpaged* pNonpaged, 
         uint8_t                         pBucketIndex)
{
    size_t
        size_bucket
            = (1 << (pBucketIndex + 5));
    
    __synapse_memory_mman_nonpaged_bucket_page*
        ptr_nonpaged_page
            = __synapse_memory_mman_nonpaged_initialize_bucket_page
                    (pNonpaged);

    for(size_t sz_alloc = 0;
               sz_alloc < __synapse_nonpaged_bucket_page_size;
               sz_alloc += size_bucket)
    {
        __synapse_memory_mman_nonpaged_bucket*
            ptr_bucket
                = __synapse_memory_mman_nonpaged_initialize_bucket
                        (pNonpaged);

        __synapse_memory_mman_nonpaged_allocate_bucket_page
            (pNonpaged, ptr_nonpaged_page);
        __synapse_memory_mman_nonpaged_allocate_bucket
            (pNonpaged, ptr_bucket,
                (uint8_t*)ptr_nonpaged_page->ptr_page
                    + sz_alloc, pBucketIndex);
    }
}