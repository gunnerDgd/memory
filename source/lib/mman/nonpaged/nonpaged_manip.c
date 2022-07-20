#include <memory/mman/nonpaged/nonpaged_manip.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>

synapse_memory_block
    synapse_memory_mman_nonpaged_allocate
        (synapse_memory_manager_handle pNonpaged, 
            void* pHint, size_t pSize)
{
    synapse_memory_opaque_init
        (synapse_memory_block, hnd_mblock,
            __synapse_memory_mman_nonpaged_allocate
                (synapse_memory_opaque_reference
                    (pNonpaged)));

    return
        hnd_mblock;
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
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    return;
}

void*
    synapse_memory_mman_nonpaged_block_pointer
        (synapse_memory_block pBlock)
{
    return
        synapse_memory_opaque_cast
            (pBlock, __synapse_memory_mman_nonpaged_block*)
                ->ptr_nonpaged;
}

size_t
    synapse_memory_mman_nonpaged_block_size
        (synapse_memory_block pBlock)
{
    return
        synapse_memory_opaque_cast
            (pBlock, __synapse_memory_mman_nonpaged_block*)
                ->sz_nonpaged;
}