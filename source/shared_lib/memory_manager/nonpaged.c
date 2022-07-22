#include <memory/export/memory_manager/nonpaged.h>

#include <memory/mman/nonpaged/nonpaged_init.h>
#include <memory/mman/nonpaged/nonpaged_manip.h>

synapse_memory_dll
    synapse_memory_manager*
	    synapse_initialize_nonpaged
            ()
{
    synapse_memory_manager*
        ptr_mman
            = synapse_system_allocate
                    (sizeof(synapse_memory_manager));

    ptr_mman->allocate
        = &synapse_memory_mman_nonpaged_allocate;
    ptr_mman->deallocate
        = &synapse_memory_mman_nonpaged_deallocate;
    ptr_mman->deallocate_all
        = &synapse_memory_mman_nonpaged_deallocate_all;
    
    ptr_mman->block_pointer
        = &synapse_memory_mman_nonpaged_block_pointer;
    ptr_mman->block_size
        = &synapse_memory_mman_nonpaged_block_size;
    
    ptr_mman->hnd_mman
        = synapse_memory_mman_nonpaged_initialize
            ();

    return ptr_mman;
}

synapse_memory_dll
    void
	    synapse_cleanup_nonpaged
		    (synapse_memory_manager* pNonpaged)
{
    synapse_memory_mman_nonpaged_cleanup
        (pNonpaged->hnd_mman);
    synapse_system_deallocate
        (pNonpaged);
}