#include <memory/pooling/static/static_pool_init.h>
#include <memory/pooling/static/details/memory_pooling_static_init.h>

synapse_memory_pool_handle
	synapse_memory_pooling_static_initialize
		(synapse_memory_manager* pMman, size_t pMpoolChunk, size_t pMpoolChunkSize)
{
	synapse_memory_pool_handle
		ptr_mpool =
			{ .opaque 
					= __synapse_memory_pooling_static_initialize
							(pMman, pMpoolChunk, pMpoolChunkSize) 
			};

	return ptr_mpool;
}

void
	synapse_memory_pooling_static_cleanup
		(synapse_memory_pool_handle pMpool)
{
	__synapse_memory_pooling_static_cleanup
		(synapse_memory_opaque_reference(pMpool));
}