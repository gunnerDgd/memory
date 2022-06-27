#include <memory/pooling/static/details/memory_pooling_static_alloc.h>

__synapse_memory_pooling_static_chunk*
__synapse_memory_pooling_static_allocate
	(__synapse_memory_pooling_static* pMpool)
{
	return
		InterlockedPopEntrySList(&pMpool->hnd_pool_stack);
}

void
__synapse_memory_pooling_static_deallocate
	(__synapse_memory_pooling_static* pMpool, __synapse_memory_pooling_static_chunk* pMpoolChunk)
{
	InterlockedPushEntrySList
		(pMpool, &pMpoolChunk->chk_slist_hnd);
}