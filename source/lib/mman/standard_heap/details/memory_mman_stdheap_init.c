#include <memory/mman/standard_heap/details/memory_mman_stdheap_init.h>
#include <memory/export/memory.h>

#include <memory/system/allocation/system_allocate.h>

#include <string.h>

__synapse_memory_mman_stdheap_head*
	__synapse_memory_mman_stdheap_initialize
		()
{
	__synapse_memory_mman_stdheap_head* 
		ptr_mman
			= synapse_memory_allocate_from_system
				(NULL, sizeof(__synapse_memory_mman_stdheap_head));

	memset
		(ptr_mman, 0x00, sizeof(__synapse_memory_mman_stdheap_head));
	return ptr_mman;
}

void
	__synapse_memory_mman_stdheap_cleanup
		(__synapse_memory_mman_stdheap_head* pMman)
{
	__synapse_memory_mman_stdheap
		*ptr_seek
			= pMman->ptr_head;

	while(ptr_seek)
	{
		__synapse_memory_mman_stdheap*
			ptr_dealloc
				= ptr_seek;

		ptr_seek
			= ptr_seek->stdheap_next;
		free
			(ptr_dealloc);
	}

	synapse_memory_deallocate_from_system
		(pMman, sizeof(__synapse_memory_mman_stdheap_head));
}