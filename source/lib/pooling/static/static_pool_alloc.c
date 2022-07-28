#include <memory/pooling/static/static_pool_alloc.h>
#include <memory/pooling/static/details/memory_pooling_static_alloc.h>

void*
	synapse_memory_pooling_static_allocate
		(synapse_memory_pool_handle pMpool)
{
	return
		__synapse_memory_pooling_static_allocate
				(synapse_memory_opaque_reference(pMpool));
}

void*
	synapse_memory_pooling_static_allocate_until_success
		(synapse_memory_pool_handle pMpool)
{
	void*
		ptr_alloc = 0;

	while
		(!(ptr_alloc
				= synapse_memory_pooling_static_allocate
						(pMpool)));
	
	return 
		ptr_alloc;
}

void
	synapse_memory_pooling_static_deallocate
		(synapse_memory_pool_handle pMpool,
		 void* 						pDeallocChunk)
{
	__synapse_memory_pooling_static_deallocate
		(synapse_memory_opaque_reference(pMpool), 
		 	(uint8_t*)pDeallocChunk
		 		- sizeof(__synapse_memory_pooling_static_block));
}