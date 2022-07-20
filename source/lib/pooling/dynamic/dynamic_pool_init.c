#include <memory/pooling/dynamic/dynamic_pool_init.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_init.h>

synapse_memory_pool_handle
	synapse_memory_pooling_dynamic_initialize
		(synapse_memory_manager* pMman, size_t pBlockSize, size_t pInitPoolSize)
{
	synapse_memory_opaque_init
		(synapse_memory_pool_handle, hnd_mpool,
			NULL);

	if(!pBlockSize || !pInitPoolSize)
		return
			hnd_mpool;

	synapse_memory_opaque_reference
		(hnd_mpool)
			= __synapse_memory_pooling_dynamic_initialize
					(pMman, pBlockSize, pInitPoolSize);

	return
		hnd_mpool;
}

void
	synapse_memory_pooling_dynamic_cleanup
		(synapse_memory_pool_handle pMpool)
{
	if (!pMpool.opaque)
		return;

	__synapse_memory_pooling_dynamic_cleanup
		(synapse_memory_opaque_reference(pMpool));
}