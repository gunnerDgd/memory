#include <memory/pooling/dynamic/dynamic_pool_alloc.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

void*
	synapse_memory_pooling_dynamic_allocate
		(synapse_memory_pool_handle pMpool)
{
	return 
		__synapse_memory_pooling_dynamic_allocate
			(synapse_memory_opaque_reference(pMpool));
}

void*
	synapse_memory_pooling_dynamic_allocate_until_success
		(synapse_memory_pool_handle pMpool)
{
	void*
		ptr_alloc = 0;
	
	while(!(ptr_alloc
				= synapse_memory_pooling_dynamic_allocate
						(pMpool)));
	
	return ptr_alloc;
}

void
	synapse_memory_pooling_dynamic_deallocate
		(synapse_memory_pool_handle pMpool, void* pDealloc)
{
	__synapse_memory_pooling_dynamic_deallocate
		(synapse_memory_opaque_reference(pMpool),
		 	(uint8_t*)pDealloc
		 			- sizeof(__synapse_memory_pooling_dynamic_block));
}

size_t
	synapse_memory_pooling_dynamic_reserve
		(synapse_memory_pool_handle pMpool, size_t pExpandSize)
{
	return
		__synapse_memory_pooling_dynamic_reserve
			(synapse_memory_opaque_reference(pMpool), pExpandSize);
}