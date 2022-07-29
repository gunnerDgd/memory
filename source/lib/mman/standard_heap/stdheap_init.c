#include <memory/mman/standard_heap/stdheap_init.h>
#include <memory/mman/standard_heap/stdheap_alloc.h>

#include <memory/mman/standard_heap/details/memory_mman_stdheap_init.h>

#include <memory/system/allocation/system_allocate.h>

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

synapse_memory_manager*
	synapse_memory_mman_stdheap_initialize_memory_manager
		()
{
	synapse_memory_manager*
		ptr_mman
			= synapse_memory_allocate_from_system
					(NULL, sizeof(synapse_memory_manager));
	
	ptr_mman->allocate
		= &synapse_memory_mman_stdheap_allocate;
	ptr_mman->deallocate
		= &synapse_memory_mman_stdheap_deallocate;
	ptr_mman->deallocate_all
		= &synapse_memory_mman_stdheap_deallocate_all;

	ptr_mman->hnd_mman
		= synapse_memory_mman_stdheap_initialize();
	return ptr_mman;
}

void
	synapse_memory_mman_stdheap_cleanup
		(synapse_memory_manager_handle pMman)
{
	__synapse_memory_mman_stdheap_cleanup
		(synapse_memory_opaque_reference(pMman));
}

void
	synapse_memory_mman_stdheap_cleanup_memory_manager
		(synapse_memory_manager* pMman)
{
	synapse_memory_mman_stdheap_cleanup
		(pMman->hnd_mman);
	synapse_memory_deallocate_from_system
		(pMman, sizeof(synapse_memory_manager));
}