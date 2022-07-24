#pragma once
#include <memory/interface/memory_pooling.h>

synapse_memory_pooled_block
	synapse_memory_pooling_dynamic_allocate
		(synapse_memory_pool_handle);

synapse_memory_pooled_block
	synapse_memory_pooling_dynamic_allocate_until_success
		(synapse_memory_pool_handle);

void
	synapse_memory_pooling_dynamic_deallocate
		(synapse_memory_pool_handle, synapse_memory_pooled_block);

size_t
	synapse_memory_pooling_dynamic_reserve
		(synapse_memory_pool_handle, size_t);

void*
	synapse_memory_pooling_dynamic_retrieve_pointer
		(synapse_memory_pooled_block);