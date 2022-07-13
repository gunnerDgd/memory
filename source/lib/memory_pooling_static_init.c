#include <memory/pooling/static/details/memory_pooling_static_init.h>
#include <memory/memory.h>

__synapse_memory_pooling_static*
__synapse_memory_pooling_static_initialize
	(synapse_memory_manager* pMman, size_t pChunkSize, size_t pChunkCount)
{
	synapse_memory_block
		hnd_mblock
			= pMman->allocate
					(pMman->hnd_mman, NULL,
						sizeof(__synapse_memory_pooling_static));

	__synapse_memory_pooling_static* 
		ptr_mpool
			= pMman->block_pointer
					(hnd_mblock);

	InitializeSListHead
		(&ptr_mpool->hnd_pool_stack);
	
	ptr_mpool->ptr_pooled_mblock
		= pMman->allocate
			(pMman->hnd_mman, NULL, pChunkSize * pChunkCount);
	ptr_mpool->ptr_pooled_memory
		= pMman->block_pointer
			(ptr_mpool->ptr_pooled_mblock);
	ptr_mpool->ptr_mpool_mblock
		= hnd_mblock;

	ptr_mpool->ptr_pool_mman
		= pMman;

	while (--pChunkCount != -1)
	{
		__synapse_memory_pooling_static_block* 
			ptr_chunk
				= _aligned_malloc
						(sizeof(__synapse_memory_pooling_static_block), 16);

		ptr_chunk->blk_pointer
			= (uint8_t*)ptr_mpool->ptr_pooled_memory 
					  + pChunkSize * pChunkCount;

		InterlockedPushEntrySList
			(&ptr_mpool->hnd_pool_stack, 
					&ptr_chunk->blk_handle);
	}

	return
		ptr_mpool;
}

void
__synapse_memory_pooling_static_cleanup
	(__synapse_memory_pooling_static* pMpool)
{
	for(__synapse_memory_pooling_static_block
			*ptr_chunk 
					= InterlockedPopEntrySList
							(&pMpool->hnd_pool_stack) ; 
			 ptr_chunk;
			 ptr_chunk 
					= InterlockedPopEntrySList
							(&pMpool->hnd_pool_stack))
								_aligned_free(ptr_chunk);
	 
	pMpool->ptr_pool_mman->deallocate
		(pMpool->ptr_pool_mman->hnd_mman,
					pMpool->ptr_pooled_mblock);
	pMpool->ptr_pool_mman->deallocate
		(pMpool->ptr_pool_mman->hnd_mman,
					pMpool->ptr_mpool_mblock);
}