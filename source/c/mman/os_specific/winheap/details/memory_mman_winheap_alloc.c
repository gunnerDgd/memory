#include <memory/mman/os_specific/winheap/details/memory_mman_winheap_alloc.h>

void*
__synapse_memory_mman_winheap_allocate
	(__synapse_memory_mman_winheap* pHeap, size_t pAllocSize)
{
	return
		HeapAlloc(pHeap->hnd_wheap, HEAP_ZERO_MEMORY, pAllocSize);
}

void
__synapse_memory_mman_winheap_deallocate
	(__synapse_memory_mman_winheap* pHeap, void* pDealloc)
{
	HeapFree
		(pHeap->hnd_wheap, 0, pDealloc);
}