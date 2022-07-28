#include <memory/pooling/static/details/memory_pooling_static_init.h>
#include <memory/pooling/static/details/memory_pooling_static_alloc.h>

#include <memory/system/allocation/system_allocate.h>

__synapse_memory_pooling_static*
	__synapse_memory_pooling_static_initialize
		(synapse_memory_manager* pMman, size_t pChunkSize, size_t pChunkCount)
{
	__synapse_memory_pooling_static* 
		ptr_mpool
			= synapse_memory_allocate_from_system
					(NULL, sizeof(__synapse_memory_pooling_static));
	
	ptr_mpool->ptr_pooled
		= pMman->allocate
			(pMman->hnd_mman, NULL, pChunkSize * pChunkCount);

	ptr_mpool->ptr_pool_mman
		= pMman;
	ptr_mpool->ptr_pool_block
		= pMman->allocate
			(pMman->hnd_mman, NULL,
				(sizeof(__synapse_memory_pooling_static_block) + pChunkSize)
					* pChunkCount);
	ptr_mpool->ptr_pool_block_stack
		= ptr_mpool->ptr_pool_block;

	return
		ptr_mpool;
}

void
__synapse_memory_pooling_static_cleanup
	(__synapse_memory_pooling_static* pMpool)
{
	pMpool->ptr_pool_mman->deallocate
		(pMpool->ptr_pool_mman->hnd_mman,
			pMpool->ptr_pool_block);
	synapse_memory_deallocate_from_system
		(pMpool, sizeof(__synapse_memory_pooling_static));
}