#include <memory/pooling/static/details/memory_pooling_static_alloc.h>

__synapse_memory_pooling_static_block*
	__synapse_memory_pooling_static_allocate
		(__synapse_memory_pooling_static* pMpool)
{
	__synapse_memory_pooling_static_block*
		ptr_mblock
			= *(__synapse_memory_pooling_static_block**)
					synapse_structure_single_linked_pop_until_success
							(pMpool->hnd_pool_stack);

	return
		ptr_mblock;
}

void
	__synapse_memory_pooling_static_deallocate
		(__synapse_memory_pooling_static	   *pMpool, 
		 __synapse_memory_pooling_static_block *pMpoolChunk)
{
	if (pMpool != pMpoolChunk->blk_pool)
		return;

	pMpoolChunk->blk_handle
		= synapse_structure_single_linked_push
			(pMpool->hnd_pool_stack,
				&pMpoolChunk, sizeof(__synapse_memory_pooling_static_block*));
}