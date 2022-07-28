#include <memory/pooling/static/details/memory_pooling_static_alloc.h>
#include <Windows.h>

void*
	__synapse_memory_pooling_static_allocate
		(__synapse_memory_pooling_static* pMpool)
{
	__synapse_memory_pooling_static_block*
		ptr_pooled_block;

	do
	{
		ptr_pooled_block
			= pMpool->ptr_pool_block_stack;
		
		if(!ptr_pooled_block)
			return NULL;
	} while (ptr_pooled_block
				!= InterlockedCompareExchange64
						(&pMpool->ptr_pool_block_stack,
							ptr_pooled_block->ptr_next, ptr_pooled_block));
		
	return
		(uint8_t*)ptr_pooled_block
			+ sizeof(__synapse_memory_pooling_static_block);
}

void
	__synapse_memory_pooling_static_deallocate
		(__synapse_memory_pooling_static	   *pMpool, 
		 __synapse_memory_pooling_static_block *pMpoolChunk)
{
	__synapse_memory_pooling_static_block*
		ptr_push;

	if (pMpool != pMpoolChunk->blk_parent_pool)
		return;

	do
	{
		ptr_push
			= pMpool->ptr_pool_block_stack;
	} while
		(ptr_push
			!= InterlockedCompareExchange64
					(&pMpool->ptr_pool_block_stack,
						ptr_push->ptr_next, ptr_push));
}