#pragma once
#include <synapse/memory/interface/memory_manager.h>
#include <synapse/memory/interface/memory_pooling.h>

synapse_memory_pooled_block
	synapse_memory_pooling_static_allocate
		(synapse_memory_pool_handle);

synapse_memory_pooled_block
	synapse_memory_pooling_static_allocate_until_success
		(synapse_memory_pool_handle);

void
	synapse_memory_pooling_static_deallocate
		(synapse_memory_pool_handle, synapse_memory_pooled_block);

void*
	synapse_memory_pooling_static_retrieve_pointer
		(synapse_memory_pooled_block);