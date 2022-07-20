#include <memory/export/init.h>
#include <memory/export/memory.h>

#include <memory/export/memory_manager/standard_heap.h>
#include <memory/export/memory_manager/nonpaged.h>

static synapse_memory_manager*
			__synapse_memory_mman;

synapse_memory_dll
void
	synapse_memory_initialize_system
		(uint16_t pSystemMman, int pArgCount, ...)
{
	if(__synapse_memory_mman)
		return;

	va_list
		ptr_init_argument;
	va_start
		(ptr_init_argument, pArgCount);
	
	switch(pSystemMman)
	{
		case SYNAPSE_MEMORY_SYSTEM_STANDARD_HEAP_MODE:
			__synapse_memory_mman
				= synapse_initialize_standard_heap();
			
			break;
		
		case SYNAPSE_MEMORY_SYSTEM_NONPAGED_POOL_MODE:
			__synapse_memory_mman
				= synapse_initialize_nonpaged
					(va_arg(ptr_init_argument, size_t));
			break;
	}
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
	synapse_memory_manager*
		synapse_system_memory_manager()
{
	return
		__synapse_memory_mman;
}

synapse_memory_dll
	void*
		synapse_system_allocate
			(size_t pSize)   { return malloc(pSize); }

synapse_memory_dll
	void
		synapse_system_deallocate
			(void* pDealloc) { return free(pDealloc); }