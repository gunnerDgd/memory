#include <memory/pooling/dynamic/details/memory_pooling_dynamic_init.h>
#include <memory/memory.h>

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
	ptr_mpool->hnd_dynamic_stack
		= synapse_structure_single_linked_initialize
				(pMman);
	
	ptr_mpool->dynamic_pool_count
		= pBlockInitCount;
	ptr_mpool->dynamic_pool_block_size
		= pBlockSize;

	while (--pBlockInitCount != -1)
	{
		__synapse_memory_pooling_dynamic_block*
			ptr_block
				= _aligned_malloc
						(sizeof(__synapse_memory_pooling_dynamic_block), 16);
		
		ptr_block->ptr_block_mblock
			= pMman->allocate
					(pMman->hnd_mman, NULL, 
							ptr_mpool->dynamic_pool_block_size);

		ptr_block->hnd_slist
			= synapse_structure_single_linked_push
				(ptr_mpool->hnd_dynamic_stack,
					&ptr_block, sizeof(__synapse_memory_pooling_dynamic_block*));
	}

	return ptr_mpool;
}

void
__synapse_memory_pooling_dynamic_cleanup
	(__synapse_memory_pooling_dynamic* pMpool)
{
	while(--pMpool->dynamic_pool_count != -1)
	{
		__synapse_memory_pooling_dynamic_block*
			ptr_block
				= *(__synapse_memory_pooling_dynamic_block**)
						synapse_structure_single_linked_pop_until_success
							(pMpool->hnd_dynamic_stack);

		pMpool->ptr_dynamic_mman->deallocate
			(pMpool->ptr_dynamic_mman->hnd_mman, 
					ptr_block->ptr_block_mblock);
		
		_aligned_free
			(ptr_block);
	}

	pMpool->ptr_dynamic_mman->deallocate
		(pMpool->ptr_dynamic_mman->hnd_mman,
				pMpool->hnd_dynamic_mblock);
}