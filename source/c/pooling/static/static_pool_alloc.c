#include <memory/pooling/static/static_pool_alloc.h>
#include <memory/pooling/static/details/memory_pooling_static_alloc.h>

synapse_memory_pooling_static_chunk
synapse_memory_pooling_static_allocate
	(synapse_memory_pooling_static pMpool, void* pAllocHint)
{
	synapse_memory_pooling_static_chunk ptr_chunk = 
		{ .opaque =
			__synapse_memory_pooling_static_allocate
				(synapse_memory_opaque_reference(pMpool))
		};

	return
		ptr_chunk;
}

void
synapse_memory_pooling_static_deallocate
	(synapse_memory_pooling_static pMpool, 
	 synapse_memory_pooling_static_chunk pDeallocChunk)
{
	__synapse_memory_pooling_static_deallocate
		(synapse_memory_opaque_reference(pMpool), 
		 synapse_memory_opaque_reference(pDeallocChunk));
}

void*
synapse_memory_pooling_static_retrieve_pointer
	(synapse_memory_pooling_static_chunk pRetriveChunk)
{
	return 
		synapse_memory_opaque_cast
			(pRetriveChunk, __synapse_memory_pooling_static_chunk*)->chk_ptr;
}