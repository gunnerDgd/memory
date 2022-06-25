#pragma once
#include <memory/defines/opaque/opaque.h>

synapse_memory_opaque_declare
	(synapse_memory_pooling_dynamic_handle)

synapse_memory_opaque_declare
	(synapse_memory_pooling_dynamic_chunk)

typedef struct synapse_memory_pooling_dynamic_traits
{
	synapse_memory_pooling_dynamic_handle
		hnd_traits;

	synapse_memory_pooling_dynamic_chunk
		(*allocate)  (synapse_memory_pooling_dynamic_handle, void*);
	void
		(*deallocate)(synapse_memory_pooling_dynamic_handle, synapse_memory_pooling_dynamic_chunk);

	size_t
		(*expand_size) (synapse_memory_pooling_dynamic_handle, size_t);
	size_t
		(*shrink_size) (synapse_memory_pooling_dynamic_handle, size_t);
	size_t
		(*current_size)(synapse_memory_pooling_dynamic_handle);
	void*
		(*retrieve_pointer)(synapse_memory_pooling_dynamic_chunk);
	
} synapse_memory_pooling_dynamic_traits;