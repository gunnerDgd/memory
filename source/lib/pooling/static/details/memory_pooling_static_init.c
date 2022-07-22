#include <memory/pooling/static/details/memory_pooling_static_init.h>
#include <memory/pooling/static/details/memory_pooling_static_alloc.h>

__synapse_memory_pooling_static*
__synapse_memory_pooling_static_initialize
	(synapse_memory_manager* pMman, size_t pChunkSize, size_t pChunkCount)
{
	synapse_memory_block
		hnd_mblock
			= pMman->allocate
					(pMman->hnd_mman, NULL,
						sizeof(__synapse_memory_pooling_static));

	__synapse_memory_pooling_static* 
		ptr_mpool
			= pMman->block_pointer
					(hnd_mblock);

	ptr_mpool->hnd_pool_stack
		= NULL;
	
	ptr_mpool->ptr_pooled_mblock
		= pMman->allocate
			(pMman->hnd_mman, NULL, pChunkSize * pChunkCount);
	ptr_mpool->ptr_pooled_memory
		= pMman->block_pointer
			(ptr_mpool->ptr_pooled_mblock);
	ptr_mpool->ptr_mpool_mblock
		= hnd_mblock;

	ptr_mpool->ptr_pool_mman
		= pMman;

	while (--pChunkCount != -1)
	{
		__synapse_memory_pooling_static_block* 
			ptr_chunk
				= __synapse_memory_pooling_static_block_initialize
						(ptr_mpool,
							(uint8_t*)ptr_mpool->ptr_pooled_memory
								+ pChunkSize);
		
		__synapse_memory_pooling_static_deallocate
			(ptr_mpool, ptr_chunk);
	}

	return
		ptr_mpool;
}

__synapse_memory_pooling_static_block*
	__synapse_memory_pooling_static_block_initialize
		(__synapse_memory_pooling_static* pStaticPool, void* pPoolMemory)
{
	synapse_memory_block
		hnd_block_memory
			= pStaticPool->ptr_pool_mman->allocate
					(pStaticPool->ptr_pool_mman->hnd_mman,
						NULL, sizeof(__synapse_memory_pooling_static_block));
	 
	 __synapse_memory_pooling_static_block*
	 	ptr_block
			= pStaticPool->ptr_pool_mman->block_pointer
					(hnd_block_memory);
	
	ptr_block->blk_parent_pool	
		= pStaticPool;
	ptr_block->blk_pointer
		= pPoolMemory;
	ptr_block->hnd_mblock_block_memory
		= hnd_block_memory;
	
	return
		ptr_block;
}

void
__synapse_memory_pooling_static_cleanup
	(__synapse_memory_pooling_static* pMpool)
{
	pMpool->ptr_pool_mman->deallocate_all
		(pMpool->ptr_pool_mman->hnd_mman);
}