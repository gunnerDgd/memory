#pragma once
#include <memory/pooling/static/static_pool_type.h>

synapse_memory_pooling_static_chunk
synapse_memory_pooling_static_allocate
	(synapse_memory_pooling_static, void*);

void
synapse_memory_pooling_static_deallocate
	(synapse_memory_pooling_static, synapse_memory_pooling_static_chunk);

void*
synapse_memory_pooling_static_retrieve_pointer
	(synapse_memory_pooling_static_chunk);