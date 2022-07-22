#include <memory/pooling/dynamic/details/memory_pooling_dynamic_init.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

#include <Windows.h>

__synapse_memory_pooling_dynamic*
__synapse_memory_pooling_dynamic_initialize	
	(synapse_memory_manager* pMman, 
			size_t pBlockSize, size_t pBlockInitCount)
{
	synapse_memory_block
		hnd_mblock_mpool
			= pMman->allocate
					(pMman->hnd_mman, NULL, 
							sizeof(__synapse_memory_pooling_dynamic));

	__synapse_memory_pooling_dynamic*
		ptr_mpool
			= pMman->block_pointer
					(hnd_mblock_mpool);

	ptr_mpool->hnd_dynamic_mblock
		= hnd_mblock_mpool;
	
	ptr_mpool->dynamic_pool_count
		= pBlockInitCount;
	ptr_mpool->dynamic_pool_block_size
		= pBlockSize;

	while (--pBlockInitCount != -1)
	{
		__synapse_memory_pooling_dynamic_block*
			ptr_dynamic_block
				= __synapse_memory_pooling_dynamic_block_initialize
						(ptr_mpool);
		
		__synapse_memory_pooling_dynamic_deallocate
			(ptr_mpool, ptr_dynamic_block);
	}

	return ptr_mpool;
}

void
__synapse_memory_pooling_dynamic_cleanup
	(__synapse_memory_pooling_dynamic* pMpool)
{
	pMpool->ptr_dynamic_mman->deallocate_all
		(pMpool->ptr_dynamic_mman->hnd_mman);
}

__synapse_memory_pooling_dynamic_block*
	__synapse_memory_pooling_dynamic_block_initialize
		(__synapse_memory_pooling_dynamic* pDynamicPool)
{
	synapse_memory_block
		hnd_block
			= pDynamicPool->ptr_dynamic_mman->allocate
				(pDynamicPool->ptr_dynamic_mman->hnd_mman,
					NULL, sizeof(__synapse_memory_pooling_dynamic_block));
	
	__synapse_memory_pooling_dynamic_block*
		ptr_block
			= pDynamicPool->ptr_dynamic_mman->block_pointer
					(hnd_block);
	
	ptr_block->mblock_block_memory
		= hnd_block;
	ptr_block->mblock_block_pooled
		= pDynamicPool->ptr_dynamic_mman->allocate
			(pDynamicPool->ptr_dynamic_mman->hnd_mman,
				NULL, pDynamicPool->dynamic_pool_block_size);
	
	ptr_block->ptr_pooled_memory
		= pDynamicPool->ptr_dynamic_mman->block_pointer
			(ptr_block->mblock_block_pooled);
	ptr_block->ptr_parent_pool
		= pDynamicPool;

	return ptr_block;
}

void
	__synapse_memory_pooling_dynamic_block_cleanup
		(__synapse_memory_pooling_dynamic*		 pDynamicPool,
		 __synapse_memory_pooling_dynamic_block* pDynamicPoolBlock)
{
	pDynamicPool->ptr_dynamic_mman->deallocate
		(pDynamicPool->ptr_dynamic_mman->hnd_mman,
			pDynamicPoolBlock->mblock_block_pooled);
	pDynamicPool->ptr_dynamic_mman->deallocate
		(pDynamicPool->ptr_dynamic_mman->hnd_mman,
			pDynamicPoolBlock->mblock_block_memory);
}