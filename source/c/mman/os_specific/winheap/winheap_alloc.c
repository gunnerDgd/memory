#include <memory/mman/os_specific/winheap/winheap_alloc.h>
#include <memory/mman/os_specific/winheap/details/memory_mman_winheap_alloc.h>

void*
synapse_memory_mman_winheap_allocate
	(synapse_memory_mman_winheap pHeap, void* pHint, size_t pSize)
{
	return
		__synapse_memory_mman_winheap_allocate
			(synapse_memory_opaque_reference(pHeap), pSize);
}

void
synapse_memory_mman_winheap_deallocate
	(synapse_memory_mman_winheap pHeap, void* pHint, size_t pSize)
{
	return
		__synapse_memory_mman_winheap_deallocate
			(synapse_memory_opaque_reference(pHeap), pHint);
}