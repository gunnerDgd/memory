#pragma once
#include <synapse/memory/interface/memory_manager.h>
#include <synapse/memory/interface/memory_pooling.h>

synapse_memory_pool_handle
	synapse_memory_pooling_static_initialize
		(synapse_memory_manager*, size_t, size_t);

void
synapse_memory_pooling_static_cleanup
	(synapse_memory_pool_handle);