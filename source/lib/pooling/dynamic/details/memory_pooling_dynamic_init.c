#include <memory/pooling/dynamic/details/memory_pooling_dynamic_init.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

#include <memory/system/allocation/system_allocate.h>

#include <Windows.h>

__synapse_memory_pooling_dynamic*
__synapse_memory_pooling_dynamic_initialize	
	(synapse_memory_manager* pMman, 
			size_t pBlockSize, size_t pBlockInitCount)
{
	__synapse_memory_pooling_dynamic*
		ptr_mpool
			= synapse_memory_aligned_allocate_from_system
					(NULL, sizeof(__synapse_memory_pooling_dynamic), 16);

	ptr_mpool->count_dynamic_pool
		= 0;
	ptr_mpool->size_dynamic_pool_block
		= pBlockSize;
	ptr_mpool->ptr_dynamic_pool_stack
		= NULL;
	ptr_mpool->ptr_dynamic_mman
		= pMman;

	__synapse_memory_pooling_dynamic_reserve
		(ptr_mpool, pBlockInitCount);

	return ptr_mpool;
}

void
__synapse_memory_pooling_dynamic_cleanup
	(__synapse_memory_pooling_dynamic* pMpool)
{
	__synapse_memory_pooling_dynamic_block*
		ptr_pooled_block
			= pMpool->ptr_dynamic_pool_stack;
	
	while(ptr_pooled_block)
	{
		__synapse_memory_pooling_dynamic_block*
			ptr_deallocate_next
				= ptr_pooled_block->ptr_next;
		
		__synapse_memory_pooling_dynamic_block_cleanup
			(pMpool, ptr_pooled_block);

		ptr_pooled_block
			= ptr_deallocate_next;
	}

	synapse_memory_aligned_deallocate_from_system
		(pMpool, sizeof(__synapse_memory_pooling_dynamic));
}

__synapse_memory_pooling_dynamic_block*
	__synapse_memory_pooling_dynamic_block_initialize
		(__synapse_memory_pooling_dynamic* pDynamicPool)
{
	__synapse_memory_pooling_dynamic_block*
		ptr_block
			= synapse_memory_aligned_allocate_from_system
					(NULL, sizeof(__synapse_memory_pooling_dynamic_block), 16);

	ptr_block->mblock_block_pooled_memory
		= pDynamicPool->ptr_dynamic_mman->allocate
			(pDynamicPool->ptr_dynamic_mman->hnd_mman,
				NULL, pDynamicPool->size_dynamic_pool_block);
	
	ptr_block->ptr_pooled_memory
		= pDynamicPool->ptr_dynamic_mman->block_pointer
			(ptr_block->mblock_block_pooled_memory);
	
	ptr_block->ptr_next
		= NULL;
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
			pDynamicPoolBlock->mblock_block_pooled_memory);
	synapse_memory_aligned_deallocate_from_system
		(pDynamicPoolBlock,
			sizeof(__synapse_memory_pooling_dynamic_block));
}