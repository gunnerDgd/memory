#include <memory/mman/nonpaged/nonpaged_init.h>
#include <memory/mman/nonpaged/details/mman_nonpaged_init.h>

synapse_memory_manager_handle
    synapse_memory_mman_nonpaged_initialize
        (size_t pBinaryPower)
{
    synapse_memory_manager_handle
        hnd_nonpaged;

    if(pBinaryPower < 5)
        pBinaryPower = 5;
    else if (pBinaryPower > 12)
        pBinaryPower = 12;

    synapse_memory_opaque_reference
        (hnd_nonpaged)
            = __synapse_memory_mman_nonpaged_initialize
                    (pBinaryPower);

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