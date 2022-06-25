#include <memory/pooling/dynamic/details/memory_pooling_dynamic_init.h>

__synapse_memory_pooling_dynamic*
__synapse_memory_pooling_dynamic_initialize	
	(synapse_memory_mman_traits* pMman, size_t pDynChunk, size_t pDynChunkInitCount)
{
	__synapse_memory_pooling_dynamic* ptr_mpool
		= malloc(sizeof(__synapse_memory_pooling_dynamic));

	InitializeSListHead
		(&ptr_mpool->hnd_dynamic_stack);
	ptr_mpool->sz_dynamic_stack_chunk
		= pDynChunk;

	while (--pDynChunkInitCount != -1)
	{
		__synapse_memory_pooling_dynamic_chunk* ptr_chunk
			= _aligned_malloc(sizeof(__synapse_memory_pooling_dynamic_chunk), 16);
		ptr_chunk->ptr_chunk
			= synapse_memory_mman_traits_allocate
				(pMman, NULL, pDynChunk);

		InterlockedPushEntrySList
			(&ptr_mpool->hnd_dynamic_stack, ptr_chunk);
	}

	return ptr_mpool;
}

void
__synapse_memory_pooling_dynamic_cleanup
	(__synapse_memory_pooling_dynamic* pMpool)
{
}