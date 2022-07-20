#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

__synapse_memory_pooling_dynamic_block*
	__synapse_memory_pooling_dynamic_allocate
		(__synapse_memory_pooling_dynamic* pMpool)
{
	__synapse_memory_pooling_dynamic_block*
		ptr_mblock
			= *(__synapse_memory_pooling_dynamic_block**)
					synapse_structure_single_linked_pop_until_success
						(pMpool->hnd_dynamic_stack);

	return
		ptr_mblock;
}

void
	__synapse_memory_pooling_dynamic_deallocate
		(__synapse_memory_pooling_dynamic		*pMpool, 
	 	 __synapse_memory_pooling_dynamic_block *pBlock)
{
	if (pBlock->ptr_block_mpool != pMpool)
		return;

	pBlock->hnd_slist
		= synapse_structure_single_linked_push
				(pMpool->hnd_dynamic_stack,
					&pBlock, sizeof(__synapse_memory_pooling_dynamic_block));		
}

size_t
__synapse_memory_pooling_dynamic_expand
	(__synapse_memory_pooling_dynamic* pMpool, size_t pExpandCount)
{
	while (--pExpandCount != -1)
	{
		__synapse_memory_pooling_dynamic_block* 
			ptr_chunk
				= _aligned_malloc
						(sizeof(__synapse_memory_pooling_dynamic_block), 16);

		ptr_chunk->ptr_block_mblock
			= pMpool->ptr_dynamic_mman->allocate
					(pMpool->ptr_dynamic_mman->hnd_mman,
							NULL, pMpool->dynamic_pool_block_size);
		ptr_chunk->ptr_block_memory
			= pMpool->ptr_dynamic_mman->block_pointer
					(ptr_chunk->ptr_block_mblock);

		ptr_chunk->hnd_slist
			= synapse_structure_single_linked_push
				(pMpool->hnd_dynamic_stack,
					&ptr_chunk, sizeof(__synapse_memory_pooling_dynamic_block*));
	}

	return
		(pMpool->dynamic_pool_count += pExpandCount);
}

size_t
__synapse_memory_pooling_dynamic_shrink
	(__synapse_memory_pooling_dynamic* pMpool, size_t pShrinkCount)
{
	if(pShrinkCount > pMpool->dynamic_pool_count)
		return
			pMpool->dynamic_pool_count;

	while (--pShrinkCount != -1)
	{
		__synapse_memory_pooling_dynamic_block* 
			ptr_chunk
				= synapse_structure_single_linked_pop_until_success
						(pMpool->hnd_dynamic_stack);

		pMpool->ptr_dynamic_mman->deallocate
			(pMpool->ptr_dynamic_mman->hnd_mman,
					ptr_chunk->ptr_block_mblock);

		_aligned_free(ptr_chunk);
	}

	return
		(pMpool->dynamic_pool_count -= pShrinkCount);
}
