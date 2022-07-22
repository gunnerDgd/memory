#include <memory/pooling/static/details/memory_pooling_static_alloc.h>
#include <Windows.h>

__synapse_memory_pooling_static_block*
	__synapse_memory_pooling_static_allocate
		(__synapse_memory_pooling_static* pMpool)
{
	__synapse_memory_pooling_static_block*
		ptr_mblock;

	do
	{
		ptr_mblock
			= pMpool->hnd_pool_stack;
		
		if(!ptr_mblock)
			return NULL;
	} while (ptr_mblock
				!= InterlockedCompareExchange64
						(&pMpool->hnd_pool_stack,
							ptr_mblock->ptr_next, ptr_mblock));
		
	return
		ptr_mblock;
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
			(&pMpool->hnd_pool_stack,
				pMpoolChunk, 0))
					goto __try_push;
	else
		return;
__try_push:
	do
	{
		ptr_push
			= pMpool->hnd_pool_stack;
	} while
		(ptr_push
			!= InterlockedCompareExchange64
					(&pMpool->hnd_pool_stack,
						ptr_push->ptr_next, ptr_push));
}