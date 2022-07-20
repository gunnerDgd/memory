#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>
#include <Windows.h>

__synapse_memory_mman_nonpaged_block*
    __synapse_memory_mman_nonpaged_allocate
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    __synapse_memory_mman_nonpaged_block*
        ptr_mblock 
            = NULL;
    
    while(!(ptr_mblock 
                = synapse_structure_single_linked_pop
                        (pNonpaged->hnd_pooled)))
        __synapse_memory_mman_nonpaged_reserve
            (pNonpaged, 1);

    return
        ptr_mblock;
}

void
    __synapse_memory_mman_nonpaged_deallocate
        (__synapse_memory_mman_nonpaged*       pNonpaged,
         __synapse_memory_mman_nonpaged_block* pNonpagedBlock)
{
    synapse_structure_single_linked_push
        (pNonpaged->hnd_pooled, pNonpagedBlock,
            sizeof(__synapse_memory_mman_nonpaged_block));
}

void
    __synapse_memory_mman_nonpaged_reserve
        (__synapse_memory_mman_nonpaged* pNonpaged, 
         size_t                          pReserveCount)
{
    while(--pReserveCount != -1)
    {
        uint8_t*
            ptr_pooled_page
                = VirtualAlloc
                    (NULL, 4096, MEM_COMMIT, PAGE_READWRITE);
        
        VirtualLock
            (ptr_pooled_page, 4096);
        
        for(size_t it_pooled = 0 ; 
                   it_pooled < 4096;
                   it_pooled += pNonpaged->size_pooled_block)
        {
            __synapse_memory_mman_nonpaged_block
                hnd_pooled_block
                    = { .ptr_nonpaged 
                            = ptr_pooled_page + it_pooled,
                        .sz_nonpaged
                            = pNonpaged->size_pooled_block
                      };

            synapse_structure_single_linked_push
                (pNonpaged->hnd_pooled, &hnd_pooled_block, 
                    sizeof(__synapse_memory_mman_nonpaged_block));
        }

        synapse_structure_double_linked_insert_back
            (pNonpaged->hnd_pooled_page,
                &ptr_pooled_page, sizeof(void*));
    }
}