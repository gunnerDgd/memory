#include <memory/mman/standard_heap/stdheap_init.h>
#include <memory/mman/standard_heap/details/memory_mman_stdheap_init.h>

synapse_memory_mman_stdheap
synapse_memory_mman_stdheap_initialize
	(size_t pBlockSize)
{
	synapse_memory_mman_stdheap ptr_mman
		= { .opaque = __synapse_memory_mman_stdheap_initialize(pBlockSize) };

	return ptr_mman;
}

void
synapse_memory_mman_stdheap_cleanup
	(synapse_memory_mman_stdheap pMman)
{
	__synapse_memory_mman_stdheap_cleanup
		(synapse_memory_opaque_reference(pMman));
}