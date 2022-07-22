#include <memory/pooling/dynamic/dynamic_pool_alloc.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

synapse_memory_pooled_block
	synapse_memory_pooling_dynamic_allocate
		(synapse_memory_pool_handle pMpool)
{
	synapse_memory_opaque_init
		(synapse_memory_pooled_block, hnd_block,
			__synapse_memory_pooling_dynamic_allocate
					(synapse_memory_opaque_reference(pMpool)));

	return hnd_block;
}

synapse_memory_pooled_block
	synapse_memory_pooling_dynamic_allocate_until_success
		(synapse_memory_pool_handle pMpool)
{
	synapse_memory_pooled_block
		hnd_block
			= { .opaque = 0 };

	while(synapse_memory_opaque_reference
				(hnd_block)
						= __synapse_memory_pooling_dynamic_allocate
								(synapse_memory_opaque_reference
									(pMpool)));

	return
		hnd_block;
}

void
	synapse_memory_pooling_dynamic_deallocate
		(synapse_memory_pool_handle pMpool, synapse_memory_pooled_block pDealloc)
{
	__synapse_memory_pooling_dynamic_deallocate
		(synapse_memory_opaque_reference(pMpool),
		 synapse_memory_opaque_reference(pDealloc));
}

size_t
	synapse_memory_pooling_dynamic_expand
		(synapse_memory_pool_handle pMpool, size_t pExpandSize)
{
	return
		__synapse_memory_pooling_dynamic_expand
			(synapse_memory_opaque_reference(pMpool), pExpandSize);
}

size_t
	synapse_memory_pooling_dynamic_shrink
		(synapse_memory_pool_handle pMpool, size_t pShrinkSize)
{
	return 
		__synapse_memory_pooling_dynamic_shrink
			(synapse_memory_opaque_reference(pMpool), pShrinkSize);
}

void*
	synapse_memory_pooling_dynamic_retrieve_pointer
		(synapse_memory_pooled_block pChunk)
{
	return
		synapse_memory_opaque_cast
			(pChunk, 
				__synapse_memory_pooling_dynamic_block*)
						->ptr_pooled_memory;
}