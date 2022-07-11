#include <memory/pooling/static/details/memory_pooling_static_alloc.h>

__synapse_memory_pooling_static_block*
	__synapse_memory_pooling_static_allocate
		(__synapse_memory_pooling_static* pMpool)
{
	__synapse_memory_pooling_static_block*
		ptr_mblock
			= InterlockedPopEntrySList
					(&pMpool->hnd_pool_stack);

	ptr_mblock->blk_pool
		= pMpool;
	return
		ptr_mblock;
}

void
	__synapse_memory_pooling_static_deallocate
		(__synapse_memory_pooling_static	   *pMpool, 
		 __synapse_memory_pooling_static_block *pMpoolChunk)
{
	if (pMpool != pMpoolChunk->blk_pointer)
		return;

	InterlockedPushEntrySList
		(pMpool, &pMpoolChunk->blk_handle);
}