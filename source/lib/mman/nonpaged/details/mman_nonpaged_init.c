#include <memory/mman/nonpaged/details/mman_nonpaged_init.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_manip.h>

#include <Windows.h>

__synapse_memory_mman_nonpaged*
    __synapse_memory_mman_nonpaged_initialize
        (size_t pBlockSize)
{
    synapse_memory_manager*
        ptr_mman
            = synapse_initialize_standard_heap();
    synapse_memory_block
        hnd_mblock
            = ptr_mman->allocate
                    (ptr_mman->hnd_mman, NULL, 
                        sizeof(__synapse_memory_mman_nonpaged));

    __synapse_memory_mman_nonpaged*
        ptr_nonpaged
            = ptr_mman->block_pointer
                    (hnd_mblock);

    ptr_nonpaged->hnd_mblock
        = hnd_mblock;
    ptr_nonpaged->hnd_mman
        = ptr_mman;

    ptr_nonpaged->hnd_pooled
        = synapse_structure_single_linked_initialize
            (ptr_mman);
    ptr_nonpaged->hnd_pooled_page
        = synapse_structure_double_linked_initialize
            (ptr_mman);

    ptr_nonpaged->size_pooled_block
        = (1 << pBlockSize);
    __synapse_memory_mman_nonpaged_reserve
        (ptr_nonpaged, 1);
}

void
    __synapse_memory_mman_nonpaged_cleanup
        (__synapse_memory_mman_nonpaged* pNonpaged)
{
    synapse_structure_double_linked_node
        ptr_deallocate
            = synapse_structure_double_linked_node_begin
                    (pNonpaged->hnd_pooled_page);

    for( ; ptr_deallocate.opaque
         ; ptr_deallocate = synapse_structure_double_linked_node_next(ptr_deallocate))
    {
        void* ptr_page
                = *(void**)
                        synapse_structure_double_linked_node_data
                            (ptr_deallocate);

        VirtualFree
            (ptr_page, 0, MEM_RELEASE);
    }

    synapse_structure_double_linked_cleanup
        (pNonpaged->hnd_pooled_page);
    synapse_structure_single_linked_cleanup
        (pNonpaged->hnd_pooled);

    pNonpaged->hnd_mman->deallocate
        (pNonpaged->hnd_mman->hnd_mman,
            pNonpaged->hnd_mblock);

    synapse_cleanup_standard_heap
        (pNonpaged->hnd_mman);
}