#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

__synapse_memory_pooling_dynamic_block*
	__synapse_memory_pooling_dynamic_allocate
		(__synapse_memory_pooling_dynamic* pMpool)
{
	return
		InterlockedPopEntrySList
			(&pMpool->hnd_dynamic_stack);
}

void
__synapse_memory_pooling_dynamic_deallocate
	(__synapse_memory_pooling_dynamic		*pMpool, 
	 __synapse_memory_pooling_dynamic_block *pBlock)
{
	if (pBlock->ptr_block_mpool != pMpool)
		return;

	InterlockedPushEntrySList
		(&pMpool->hnd_dynamic_stack, &pBlock->hnd_slist);
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
							NULL, pMpool->sz_dynamic_pool_block);
		ptr_chunk->ptr_block_memory
			= pMpool->ptr_dynamic_mman->block_pointer
					(ptr_chunk->ptr_block_mblock);
		

		InterlockedPushEntrySList
			(&pMpool->hnd_dynamic_stack, 
					&ptr_chunk->hnd_slist);
	}

	return
		(pMpool->cnt_dynamic_pool += pExpandCount);
}

size_t
__synapse_memory_pooling_dynamic_shrink
	(__synapse_memory_pooling_dynamic* pMpool, size_t pShrinkCount)
{
	if(pShrinkCount > pMpool->cnt_dynamic_pool)
		return
			pMpool->cnt_dynamic_pool;

	while (--pShrinkCount != -1)
	{
		__synapse_memory_pooling_dynamic_block* 
			ptr_chunk;
		while
			(!(ptr_chunk 
					= InterlockedPopEntrySList
							(&pMpool->hnd_dynamic_stack)));

		pMpool->ptr_dynamic_mman->deallocate
			(pMpool->ptr_dynamic_mman->hnd_mman,
					ptr_chunk->ptr_block_mblock);

		_aligned_free(ptr_chunk);
	}

	return
		(pMpool->cnt_dynamic_pool -= pShrinkCount);
}
