#include <memory/mman/standard_heap/stdheap_alloc.h>
#include <memory/mman/standard_heap/details/memory_mman_stdheap_alloc.h>

void*
	synapse_memory_mman_stdheap_allocate
		(synapse_memory_manager_handle pMman, void* pHint, size_t pSize)
{
	return
		__synapse_memory_mman_stdheap_allocate
				(synapse_memory_opaque_reference(pMman), pHint, pSize);
}

void
synapse_memory_mman_stdheap_deallocate
	(synapse_memory_manager_handle pMman, void* pBlock)
{
	__synapse_memory_mman_stdheap_deallocate
		(synapse_memory_opaque_reference(pMman),
		 (uint8_t*)pBlock - sizeof(__synapse_memory_mman_stdheap));
}

void
synapse_memory_mman_stdheap_deallocate_all
	(synapse_memory_manager_handle pHeap)
{
	__synapse_memory_mman_stdheap_deallocate_all
		(synapse_memory_opaque_reference(pHeap));
}