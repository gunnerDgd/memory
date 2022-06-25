#include <memory/mman/os_specific/winheap/details/memory_mman_winheap_init.h>

__synapse_memory_mman_winheap*
__synapse_memory_mman_winheap_initialize
	(size_t pInitSize, size_t pMaxSize)
{
	__synapse_memory_mman_winheap* ptr_wheap
		= malloc(sizeof(__synapse_memory_mman_winheap));

	ptr_wheap->hnd_wheap
		= HeapCreate(0, pInitSize, pMaxSize);
	ptr_wheap->sz_wheap_init
		= pInitSize;
	ptr_wheap->sz_wheap_max
		= pMaxSize;
}

void
__synapse_memory_mman_winheap_cleanup
	(__synapse_memory_mman_winheap* pHeap)
{
	HeapDestroy(pHeap->hnd_wheap);
	free	   (pHeap);
}