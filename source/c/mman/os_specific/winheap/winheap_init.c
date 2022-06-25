#include <memory/mman/os_specific/winheap/winheap_init.h>
#include <memory/mman/os_specific/winheap/details/memory_mman_winheap_init.h>

synapse_memory_mman_winheap
synapse_memory_mman_winheap_initialize
	(size_t pInitSize, size_t pMaxSize)
{
	synapse_memory_mman_winheap ptr_wheap =
		{ .opaque = __synapse_memory_mman_winheap_initialize(pInitSize, pMaxSize) };

	return ptr_wheap;
}

void
synapse_memory_mman_winheap_cleanup
	(synapse_memory_mman_winheap pHeap)
{
	__synapse_memory_mman_winheap_cleanup
		(synapse_memory_opaque_reference(pHeap));
}