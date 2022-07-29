#include <memory/mman/nonpaged/nonpaged_manip.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>

void*
    synapse_memory_mman_nonpaged_allocate
        (synapse_memory_manager_handle pNonpaged, 
            void* pHint, size_t pSize)
{
    uint8_t
        idx_bucket = 9;
    
    for ( ; idx_bucket >= 5 ; idx_bucket--)
        if(pSize == (1 << idx_bucket))
            break;
        else if (pSize & (1 << idx_bucket))
            break;
    
    return
        __synapse_memory_mman_nonpaged_allocate
            (synapse_memory_opaque_reference
                (pNonpaged), idx_bucket - 5);
}

void
    synapse_memory_mman_nonpaged_deallocate
        (synapse_memory_manager_handle pNonpaged, void* pDealloc)
{
    __synapse_memory_mman_nonpaged_deallocate
        (synapse_memory_opaque_reference
            (pNonpaged),
         (uint8_t*)pDealloc
            - sizeof(__synapse_memory_mman_nonpaged_block));
}

void
    synapse_memory_mman_nonpaged_deallocate_all
        (synapse_memory_manager_handle pNonpaged)
{
    return;
}