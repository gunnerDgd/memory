#include <memory/mman/nonpaged/nonpaged_manip.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>

synapse_memory_block
    synapse_memory_mman_nonpaged_allocate
        (synapse_memory_manager_handle pNonpaged, 
            void* pHint, size_t pSize)
{
    synapse_memory_opaque_init
        (synapse_memory_block, hnd_memory, NULL);
    
    if(pSize > (1 << 9))
        return hnd_memory;
    
    for(size_t it_index = 9 ;
               it_index >= 5;
               it_index--)
        if((1 << it_index) & pSize)
        {
__nonpaged_alloc:
            synapse_memory_opaque_reference
                (hnd_memory)
                    = __synapse_memory_mman_nonpaged_allocate
                            (synapse_memory_opaque_reference
                                (pNonpaged), it_index - 5);
            
            if(!synapse_memory_opaque_reference
                    (hnd_memory))
            {
                __synapse_memory_mman_nonpaged_reserve
                    (synapse_memory_opaque_reference
                        (pNonpaged), it_index - 5);
                
                goto __nonpaged_alloc;
            }
            
            break;
        }

    return
        hnd_memory;
}

void
    synapse_memory_mman_nonpaged_deallocate
        (synapse_memory_manager_handle pNonpaged, synapse_memory_block pBlock)
{
    __synapse_memory_mman_nonpaged_deallocate
        (synapse_memory_opaque_reference
            (pNonpaged),
         synapse_memory_opaque_reference
            (pBlock));
}

void
    __synapse_memory_mman_nonpaged_deallocate_all
        (synapse_memory_manager_handle pNonpaged)
{
    return;
}

void*
    synapse_memory_mman_nonpaged_block_pointer
        (synapse_memory_block pBlock)
{
    return
        synapse_memory_opaque_cast
            (pBlock, __synapse_memory_mman_nonpaged_bucket*)
                ->ptr_nonpaged;
}

size_t
    synapse_memory_mman_nonpaged_block_size
        (synapse_memory_block pBlock)
{
    return
        (synapse_memory_opaque_cast
            (pBlock, __synapse_memory_mman_nonpaged_bucket*)
                ->idx_nonpaged_index << 5);
}