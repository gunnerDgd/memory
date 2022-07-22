#include <memory/pooling/dynamic/details/memory_pooling_dynamic_init.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>
#include <Windows.h>

__synapse_memory_pooling_dynamic_block*
	__synapse_memory_pooling_dynamic_allocate
		(__synapse_memory_pooling_dynamic* pMpool)
{
	__synapse_memory_pooling_dynamic_block*
		ptr_mblock;

	do
	{
		ptr_mblock
			= pMpool->hnd_dynamic_stack;
		
		if(!ptr_mblock)
			return NULL;
	} while
		(ptr_mblock 
			!= InterlockedCompareExchange64
					(&pMpool->hnd_dynamic_stack,
						ptr_mblock->ptr_next, ptr_mblock));

	return
		ptr_mblock;
}

void
	__synapse_memory_pooling_dynamic_deallocate
		(__synapse_memory_pooling_dynamic		*pDynamicPool, 
	 	 __synapse_memory_pooling_dynamic_block *pDynamicPoolBlock)
{
	if (pDynamicPoolBlock->ptr_parent_pool 
				!= pDynamicPool)
		return;

__try_first_push:
	if(InterlockedCompareExchange64
			(&pDynamicPool->hnd_dynamic_stack,
				pDynamicPoolBlock, 0))
					goto __try_push;
	else
		return;
__try_push:
	do
	{
		pDynamicPoolBlock->ptr_next
			= pDynamicPool->hnd_dynamic_stack;
	} while
		(pDynamicPool->hnd_dynamic_stack
			!= InterlockedCompareExchange64
					(&pDynamicPool->hnd_dynamic_stack,
						pDynamicPoolBlock,
							pDynamicPool->ptr_dynamic_mman));
	return;
}

size_t
__synapse_memory_pooling_dynamic_expand
	(__synapse_memory_pooling_dynamic* pMpool, size_t pExpandCount)
{
	while (--pExpandCount != -1)
	{
		__synapse_memory_pooling_dynamic_block*
			ptr_block
				= __synapse_memory_pooling_dynamic_block_initialize
						(pMpool);
		
		__synapse_memory_pooling_dynamic_deallocate
			(pMpool, ptr_block);
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
			ptr_block
				= __synapse_memory_pooling_dynamic_allocate
						(pMpool);

		__synapse_memory_pooling_dynamic_block_cleanup
			(pMpool, ptr_block);
	}

	return
		(pMpool->dynamic_pool_count -= pShrinkCount);
}
