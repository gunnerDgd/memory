#include <memory/pooling/dynamic/dynamic_pool_init.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_init.h>

synapse_memory_pooling_dynamic
synapse_memory_pooling_dynamic_initialize
	(synapse_memory_mman_traits* pMman, size_t pMpoolChunk, size_t pMpoolInitChunkCount)
{
	synapse_memory_pooling_dynamic ptr_mpool = 
		{ .opaque = __synapse_memory_pooling_dynamic_initialize
			(pMman, pMpoolChunk, pMpoolInitChunkCount) };

	return
		ptr_mpool;
}

void
synapse_memory_pooling_dynamic_cleanup
	(synapse_memory_pooling_dynamic pMpool)
{
	__synapse_memory_pooling_dynamic_cleanup
		(synapse_memory_opaque_reference(pMpool));
}