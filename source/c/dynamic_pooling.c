#include <synapse/memory/pooling/dynamic_pooling/dynamic_pooling.h>
#include <synapse/memory/memory.h>

#include <memory/pooling/dynamic/dynamic_pool.h>
#include <stdlib.h>

synapse_memory_dll
synapse_memory_dynamic_pool*
	synapse_initialize_dynamic_pool
		(synapse_memory_manager* pMman, 
				size_t pBlockSize, size_t pInitBlockCount)
{
	synapse_memory_dynamic_pool*
		ptr_mpool
			= malloc
					(sizeof(synapse_memory_dynamic_pool));

	ptr_mpool->allocate
		= &synapse_memory_pooling_dynamic_allocate;
	ptr_mpool->allocate_until_success
		= &synapse_memory_pooling_dynamic_allocate_until_success;
	ptr_mpool->deallocate
		= &synapse_memory_pooling_dynamic_deallocate;

	ptr_mpool->expand_pool_size
		= &synapse_memory_pooling_dynamic_expand;
	ptr_mpool->shrink_pool_size
		= &synapse_memory_pooling_dynamic_shrink;

	ptr_mpool->hnd_static_pool
		= synapse_memory_pooling_dynamic_initialize
				(pMman, pBlockSize, pInitBlockCount);

	return
		ptr_mpool;
}

synapse_memory_dll
void
	synapse_cleanup_dynamic_pool
		(synapse_memory_dynamic_pool* pMpool)
{
	synapse_memory_pooling_dynamic_cleanup
		(pMpool->hnd_static_pool);
	free
		(pMpool);
}