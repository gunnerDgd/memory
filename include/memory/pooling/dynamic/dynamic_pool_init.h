#pragma once
#include <synapse/memory/interface/memory_pooling.h>
#include <synapse/memory/interface/memory_manager.h>

synapse_memory_pool_handle
	synapse_memory_pooling_dynamic_initialize
		(synapse_memory_manager*, size_t, size_t);

void
synapse_memory_pooling_dynamic_cleanup
	(synapse_memory_pool_handle);