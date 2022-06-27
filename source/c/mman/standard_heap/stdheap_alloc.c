#include <memory/mman/standard_heap/stdheap_alloc.h>
#include <memory/mman/standard_heap/details/memory_mman_stdheap_alloc.h>

void*
synapse_memory_mman_stdheap_allocate
	(synapse_memory_mman_stdheap pMman, void* pHint, size_t pSize)
{
	return
		__synapse_memory_mman_stdheap_allocate
			(synapse_memory_opaque_reference(pMman), pHint, pSize);
}

void
synapse_memory_mman_stdheap_deallocate
	(synapse_memory_mman_stdheap pMman, void* pHint, size_t pSize)
{
	__synapse_memory_mman_stdheap_deallocate
		(synapse_memory_opaque_reference(pMman), pHint, pSize);
}

size_t
synapse_memory_mman_stdheap_alloc_unit
	(synapse_memory_mman_stdheap pMman)
{
	return
		__synapse_memory_mman_stdheap_alloc_unit
			(synapse_memory_opaque_reference(pMman));
}