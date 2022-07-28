#include <memory/export/memory_manager/standard_heap.h>
#include <memory/export/memory.h>

#include <memory/mman/standard_heap/stdheap.h>
#include <stdlib.h>

synapse_memory_dll
	synapse_memory_manager*
		synapse_initialize_standard_heap()
{
	synapse_memory_manager*
		ptr_mman
			= malloc
					(sizeof(synapse_memory_manager));

	ptr_mman->allocate
		= &synapse_memory_mman_stdheap_allocate;
	ptr_mman->deallocate
		= &synapse_memory_mman_stdheap_deallocate;
	ptr_mman->deallocate_all
		= &synapse_memory_mman_stdheap_deallocate_all;
	ptr_mman->hnd_mman
		= synapse_memory_mman_stdheap_initialize();

	return
		ptr_mman;
}

synapse_memory_dll
	void
		synapse_cleanup_standard_heap
			(synapse_memory_manager* pMman)
{
	synapse_memory_mman_stdheap_cleanup
		(pMman->hnd_mman);
	free
		(pMman);
}