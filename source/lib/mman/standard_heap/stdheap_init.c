#include <memory/mman/standard_heap/stdheap_init.h>
#include <memory/mman/standard_heap/details/memory_mman_stdheap_init.h>

synapse_memory_manager_handle
	synapse_memory_mman_stdheap_initialize
		()
{
	synapse_memory_opaque_init
		(synapse_memory_manager_handle, hnd_stdheap,
			__synapse_memory_mman_stdheap_initialize());

	return 
		hnd_stdheap;
}

void
	synapse_memory_mman_stdheap_cleanup
		(synapse_memory_manager_handle pMman)
{
	__synapse_memory_mman_stdheap_cleanup
		(synapse_memory_opaque_reference(pMman));
}