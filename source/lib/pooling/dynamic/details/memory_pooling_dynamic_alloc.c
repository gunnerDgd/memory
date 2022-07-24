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
			= pMpool->ptr_dynamic_pool_stack;
		
		if(!ptr_mblock)
			return NULL;
	} while
		(ptr_mblock 
			!= InterlockedCompareExchange64
					(&pMpool->ptr_dynamic_pool_stack,
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

	pDynamicPoolBlock->ptr_next
		= NULL;
	do
	{
		pDynamicPoolBlock->ptr_next
			= pDynamicPool->ptr_dynamic_pool_stack;
	} while
		(pDynamicPoolBlock->ptr_next
			!= InterlockedCompareExchange64
					(&pDynamicPool->ptr_dynamic_pool_stack,
						pDynamicPoolBlock,
							pDynamicPoolBlock->ptr_next));

	return;
}

size_t
	__synapse_memory_pooling_dynamic_reserve
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
		(pMpool->count_dynamic_pool += pExpandCount);
}