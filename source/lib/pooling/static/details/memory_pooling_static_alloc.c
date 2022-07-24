#include <memory/pooling/static/details/memory_pooling_static_alloc.h>
#include <Windows.h>

__synapse_memory_pooling_static_block*
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
		ptr_pooled_block;
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

__try_first_push:
	if(InterlockedCompareExchange64
			(&pMpool->ptr_pool_block_stack,
				pMpoolChunk, 0))
					goto __try_push;
	else
		return;
__try_push:
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