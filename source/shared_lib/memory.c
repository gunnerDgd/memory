#include <memory/memory.h>
#include <memory/standard_heap.h>

#include <stdlib.h>

static synapse_memory_manager*
			__synapse_memory_mman;

synapse_memory_dll
void
	synapse_memory_initialize_system
		()
{
	if(!__synapse_memory_mman)
		__synapse_memory_mman
			= synapse_initialize_standard_heap();
}

synapse_memory_dll
void
	synapse_memory_cleanup_system
		()
{
	if(__synapse_memory_mman)
		synapse_cleanup_standard_heap
			(__synapse_memory_mman);

	__synapse_memory_mman
		= NULL;
}

synapse_memory_dll
synapse_memory_block
	synapse_memory_allocate
		(size_t pSize)
			
{
	return
		__synapse_memory_mman->allocate
			(__synapse_memory_mman->hnd_mman,
				NULL, pSize);
}

synapse_memory_dll
void
	synapse_memory_deallocate
		(synapse_memory_block pDealloc)
{ 
	__synapse_memory_mman->deallocate
		(__synapse_memory_mman->hnd_mman,
				pDealloc);
}
