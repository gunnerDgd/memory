#pragma once
#include <memory/pooling/dynamic/dynamic_pool_type.h>
#include <memory/mman/mman_traits.h>

synapse_memory_pooling_dynamic
synapse_memory_pooling_dynamic_initialize
	(synapse_memory_mman_traits*, size_t, size_t);

void
synapse_memory_pooling_dynamic_cleanup
	(synapse_memory_pooling_dynamic);