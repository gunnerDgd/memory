#include <memory/mman/nonpaged/details/mman_nonpaged_init.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>

#include <Windows.h>

void*
    __synapse_memory_mman_nonpaged_allocate
        (__synapse_memory_mman_nonpaged* pNonpaged, size_t pAllocRound)
{
    __synapse_memory_mman_nonpaged_block*
        ptr_mblock 
            = NULL;

    do
    {
        ptr_mblock
            = pNonpaged->hnd_pooled[pAllocRound].ptr_bucket_block;
        
        if(!ptr_mblock)
            return NULL;
    } while
        (ptr_mblock
            != InterlockedCompareExchange64
                    (&pNonpaged->hnd_pooled[pAllocRound].ptr_bucket_block,
                        ptr_mblock->ptr_next_block,
                            ptr_mblock));

    return
        (uint8_t*)ptr_mblock
            + sizeof(__synapse_memory_mman_nonpaged_block);
}

void
    __synapse_memory_mman_nonpaged_deallocate
        (__synapse_memory_mman_nonpaged*       pNonpaged,
         __synapse_memory_mman_nonpaged_block* pNonpagedBlock)
{
    __synapse_memory_mman_nonpaged_block*
        ptr_bucket;

    if(pNonpagedBlock->ptr_nonpaged_parent
            != pNonpaged)
                    return;

    do
    {
        ptr_bucket
            = pNonpaged->hnd_pooled;
        pNonpagedBlock->ptr_next_block
            = ptr_bucket;
    } while
        (ptr_bucket
            != InterlockedCompareExchange64
                    (&pNonpaged->hnd_pooled,
                        pNonpagedBlock, ptr_bucket));

    return;
}

void
    __synapse_memory_mman_nonpaged_reserve_page
        (__synapse_memory_mman_nonpaged*      pNonpaged, 
         __synapse_memory_mman_nonpaged_page* pNonpagedPage)
{
    do
    {
        pNonpagedPage->ptr_next
            = pNonpaged->hnd_pooled_page;
    } while
        (pNonpagedPage->ptr_next
            != InterlockedCompareExchange64
                    (&pNonpaged->hnd_pooled_page,
                        pNonpagedPage,
                            pNonpagedPage->ptr_next));
}

void
    __synapse_memory_mman_nonpaged_reserve
        (__synapse_memory_mman_nonpaged* pNonpaged, 
         uint8_t                         pBucketIndex)
{
    size_t
        size_bucket
            = (1 << (pBucketIndex + 5)),
        count_bucket
            = __synapse_memory_mman_nonpaged_page_size
                / (sizeof(__synapse_memory_mman_nonpaged_block) + size_bucket);
    
    __synapse_memory_mman_nonpaged_page*
        ptr_nonpaged_page
            = __synapse_memory_mman_nonpaged_initialize_page
                    (pNonpaged);
    __synapse_memory_mman_nonpaged_block
        *ptr_block_reserve
            = ptr_nonpaged_page->ptr_alloc_page;
    
    __synapse_memory_mman_nonpaged_reserve_page
        (pNonpaged, ptr_nonpaged_page);

    for(size_t it_reserve = 0;
               it_reserve < count_bucket - 1;
               it_reserve++)
    {
        ptr_block_reserve->ptr_nonpaged_parent
            = pNonpaged;
        ptr_block_reserve->ptr_next_block
            = (uint8_t*)ptr_block_reserve + size_bucket;
        
        do
        {
            ptr_block_reserve->ptr_next_block
                = pNonpaged->hnd_pooled;
        } while
            (ptr_block_reserve->ptr_next_block
                != InterlockedCompareExchange64
                        (&pNonpaged->hnd_pooled_page,
                            ptr_block_reserve,
                                ptr_block_reserve->ptr_next_block));

        ptr_block_reserve
            = ptr_block_reserve->ptr_next_block;
    }

    ptr_block_reserve->ptr_next_block->ptr_nonpaged_parent
        = pNonpaged;
}