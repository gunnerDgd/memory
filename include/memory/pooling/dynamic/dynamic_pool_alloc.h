#pragma once
#include <memory/pooling/dynamic/dynamic_pool_type.h>

synapse_memory_pooling_dynamic_chunk
synapse_memory_pooling_dynamic_allocate
	(synapse_memory_pooling_dynamic, void*);

void
synapse_memory_pooling_dynamic_deallocate
	(synapse_memory_pooling_dynamic, synapse_memory_pooling_dynamic_chunk);

size_t
synapse_memory_pooling_dynamic_expand
	(synapse_memory_pooling_dynamic, size_t);

size_t
synapse_memory_pooling_dynamic_shrink
	(synapse_memory_pooling_dynamic, size_t);

size_t
synapse_memory_pooling_dynamic_current_size
	(synapse_memory_pooling_dynamic);

void*
synapse_memory_pooling_dynamic_retrieve_pointer
	(synapse_memory_pooling_dynamic_chunk);