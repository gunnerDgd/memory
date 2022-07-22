#include <memory/export/memory.h>
#include <memory/export/pooling/static_pooling.h>

#include <memory/pooling/static/static_pool.h>
#include <stdlib.h>

synapse_memory_dll
	synapse_memory_static_pool*
		synapse_initialize_static_pool
			(size_t pBlockSize, size_t pBlockCount)
{
	synapse_memory_static_pool*
		hnd_static_pool;
	
	if (!pBlockSize || !pBlockCount)
		return NULL;

	hnd_static_pool
		= synapse_system_allocate
			(sizeof(synapse_memory_static_pool));

	hnd_static_pool
		->allocate
			= &synapse_memory_pooling_static_allocate;
	hnd_static_pool
		->allocate_until_success
			= &synapse_memory_pooling_static_allocate_until_success;
	hnd_static_pool
		->deallocate
			= &synapse_memory_pooling_static_deallocate;

	hnd_static_pool
		->hnd_static_pool
			= synapse_memory_pooling_static_initialize
					(synapse_system_memory_manager(), 
						pBlockSize, pBlockCount);

	return
		hnd_static_pool;
}

synapse_memory_dll
	void
		synapse_cleanup_static_pool
			(synapse_memory_static_pool* pMpool)
{
	synapse_memory_pooling_static_cleanup
		(pMpool->hnd_static_pool);
	synapse_system_deallocate
		(pMpool);
}