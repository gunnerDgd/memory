#include <memory/export/init.h>
#include <memory/export/memory.h>

#include <memory/system/allocation/system_allocate.h>
#include <memory/system/allocation/system_page.h>

#include <memory/mman/standard_heap/stdheap.h>
#include <memory/mman/nonpaged/nonpaged_init.h>

#include <stdlib.h>

static synapse_memory_manager*
			__synapse_memory_mman;
static uint16_t
			__synapse_memory_mman_type;

synapse_memory_dll
void
	synapse_memory_initialize_system
		(uint16_t pSystemMman)
{
	if(__synapse_memory_mman)
		return;

	__synapse_memory_mman_type
		= pSystemMman;

	switch(pSystemMman)
	{
		case SYNAPSE_MEMORY_SYSTEM_STANDARD_HEAP_MODE:
			__synapse_memory_mman
				= synapse_memory_mman_stdheap_initialize_memory_manager();
			
			break;
		
		case SYNAPSE_MEMORY_SYSTEM_NONPAGED_POOL_MODE:
			__synapse_memory_mman
				= synapse_memory_mman_nonpaged_initialize_memory_manager();
			
			break;
	}
}

synapse_memory_dll
void 
	synapse_memory_cleanup_system
		()
{
	if(!__synapse_memory_mman)
		return;

	switch(__synapse_memory_mman_type)
	{
		case SYNAPSE_MEMORY_SYSTEM_STANDARD_HEAP_MODE:
			synapse_memory_mman_stdheap_cleanup_memory_manager
				(__synapse_memory_mman);
			break;
		
		case SYNAPSE_MEMORY_SYSTEM_NONPAGED_POOL_MODE:
			synapse_memory_mman_nonpaged_cleanup_memory_manager
				(__synapse_memory_mman);
			
			break;
	}

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
			(size_t pSize)
{ 
	return 
		synapse_memory_allocate_from_system
			(NULL, pSize); 
}

synapse_memory_dll
	void
		synapse_system_deallocate
			(void* pDealloc) 
{ 
	synapse_memory_deallocate_from_system
		(pDealloc, 0);
}

synapse_memory_dll
	void*
		synapse_system_aligned_allocate
			(size_t pAllocSize, size_t pAllocAlign)
{
	return
		synapse_memory_aligned_allocate_from_system
			(NULL, pAllocSize, pAllocAlign);
}

synapse_memory_dll
	void
		synapse_system_aligned_deallocate
			(void* pDealloc)
{
	synapse_memory_aligned_deallocate_from_system
		(pDealloc, 0);
}

synapse_memory_dll
	void*
		synapse_system_allocate_page
			(void* pAllocHint, size_t pAllocSize)
{
	return
		synapse_memory_allocate_page_from_system
			(pAllocHint, pAllocSize);
}

synapse_memory_dll
	void
		synapse_system_deallocate_page
			(void* pDealloc, size_t pDeallocSize)
{
	return
		synapse_memory_deallocate_page_from_system
			(pDealloc, pDeallocSize);
}