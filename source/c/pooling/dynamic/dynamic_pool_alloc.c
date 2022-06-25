#include <memory/pooling/dynamic/dynamic_pool_alloc.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

synapse_memory_pooling_dynamic_chunk
synapse_memory_pooling_dynamic_allocate
	(synapse_memory_pooling_dynamic pMpool, void* pAllocHint)
{
	synapse_memory_pooling_dynamic_chunk ptr_chunk =
		{ .opaque = __synapse_memory_pooling_dynamic_allocatea
						(synapse_memory_opaque_reference(pMpool), pAllocHint)};

	return ptr_chunk;
}

void
synapse_memory_pooling_dynamic_deallocate
	(synapse_memory_pooling_dynamic pMpool, synapse_memory_pooling_dynamic_chunk pDealloc)
{
	__synapse_memory_pooling_dynamic_deallocate
		(synapse_memory_opaque_reference(pMpool),
		 synapse_memory_opaque_reference(pDealloc));
}

size_t
synapse_memory_pooling_dynamic_expand
	(synapse_memory_pooling_dynamic pMpool, size_t pExpandSize)
{
	__synapse_memory_pooling_dynamic_expand
		(synapse_memory_opaque_reference(pMpool), pExpandSize);
}

size_t
synapse_memory_pooling_dynamic_shrink
	(synapse_memory_pooling_dynamic pMpool, size_t pShrinkSize)
{
	__synapse_memory_pooling_dynamic_shrink
		(synapse_memory_opaque_reference(pMpool), pShrinkSize);
}

size_t
synapse_memory_pooling_dynamic_current_size
	(synapse_memory_pooling_dynamic pMpool)
{
	return
		__synapse_memory_pooling_dynamic_current_size
			(synapse_memory_opaque_reference(pMpool));
}

void*
synapse_memory_pooling_dynamic_retrieve_pointer
	(synapse_memory_pooling_dynamic_chunk pChunk)
{
	return
		synapse_memory_opaque_cast
			(pChunk, __synapse_memory_pooling_dynamic_chunk*)->ptr_chunk;
}