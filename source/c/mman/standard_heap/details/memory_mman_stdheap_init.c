#include <memory/mman/standard_heap/details/memory_mman_stdheap_init.h>
#include <stdlib.h>

__synapse_memory_mman_stdheap*
__synapse_memory_mman_stdheap_initialize
	(size_t pAllocUnit)
{
	__synapse_memory_mman_stdheap* ptr_mman
		= malloc(sizeof(__synapse_memory_mman_stdheap));

	ptr_mman->sz_stdheap_alloc_unit
		= pAllocUnit;
	return ptr_mman;
}

void
__synapse_memory_mman_stdheap_cleanup
	(__synapse_memory_mman_stdheap* pMman)
{
	free(pMman);
}