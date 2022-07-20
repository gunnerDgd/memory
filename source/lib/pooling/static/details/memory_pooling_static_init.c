#include <memory/pooling/static/details/memory_pooling_static_init.h>
#include <memory/memory.h>

#include <stdalign.h>

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

	ptr_mpool->hnd_pool_stack
		= synapse_structure_single_linked_initialize
				(pMman);
	
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
		ptr_chunk->blk_pool
			= ptr_mpool;

		ptr_chunk->blk_handle
			= synapse_structure_single_linked_push
					(ptr_mpool->hnd_pool_stack,
							&ptr_chunk, sizeof(__synapse_memory_pooling_static_block*));
	}

	return
		ptr_mpool;
}

void
__synapse_memory_pooling_static_cleanup
	(__synapse_memory_pooling_static* pMpool)
{
	synapse_structure_single_linked_cleanup
		(pMpool->hnd_pool_stack);
	pMpool->ptr_pool_mman->deallocate
		(pMpool->ptr_pool_mman->hnd_mman,
					pMpool->ptr_pooled_mblock);
	pMpool->ptr_pool_mman->deallocate
		(pMpool->ptr_pool_mman->hnd_mman,
					pMpool->ptr_mpool_mblock);
}