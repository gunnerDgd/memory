#include <memory/mman/standard_heap/details/memory_mman_stdheap_alloc.h>
#include <stdlib.h>

void*
__synapse_memory_mman_stdheap_allocate
	(__synapse_memory_mman_stdheap* pMman, void* pHint, size_t pSize)
{
	return
		malloc(pMman->sz_stdheap_alloc_unit * pSize);
}

void
__synapse_memory_mman_stdheap_deallocate
	(__synapse_memory_mman_stdheap* pMman, void* pDealloc, size_t pSize)
{
	free(pDealloc);
}

size_t
__synapse_memory_mman_stdheap_alloc_unit
	(__synapse_memory_mman_stdheap* pMman) { return pMman->sz_stdheap_alloc_unit; }