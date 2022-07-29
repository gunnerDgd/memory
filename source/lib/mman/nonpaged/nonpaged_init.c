#include <memory/mman/nonpaged/nonpaged_init.h>
#include <memory/mman/nonpaged/nonpaged_manip.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_init.h>

#include <memory/system/allocation/system_allocate.h>

synapse_memory_manager_handle
    synapse_memory_mman_nonpaged_initialize
        (size_t pBinaryPower)
{
    synapse_memory_opaque_init
        (synapse_memory_manager_handle, hnd_nonpaged,
            __synapse_memory_mman_nonpaged_initialize());
    
    return
        hnd_nonpaged;
}

void
    synapse_memory_mman_nonpaged_cleanup
        (synapse_memory_manager_handle pNonpaged)
{
    __synapse_memory_mman_nonpaged_cleanup
        (synapse_memory_opaque_reference
            (pNonpaged));
}

synapse_memory_manager*
    synapse_memory_mman_nonpaged_initialize_memory_manager
        ()
{
    synapse_memory_manager*
        ptr_mman
            = synapse_memory_allocate_from_system
                    (NULL, sizeof(synapse_memory_manager));
    
    ptr_mman->allocate
        = &synapse_memory_mman_nonpaged_allocate;
    ptr_mman->deallocate
        = &synapse_memory_mman_nonpaged_deallocate;
    ptr_mman->deallocate_all
        = NULL;

    return ptr_mman;
}

void
    synapse_memory_mman_nonpaged_cleanup_memory_manager
        (synapse_memory_manager* pMman)
{
    synapse_memory_mman_nonpaged_cleanup
        (pMman->hnd_mman);
    synapse_memory_deallocate_from_system
        (pMman, sizeof(synapse_memory_manager));
}