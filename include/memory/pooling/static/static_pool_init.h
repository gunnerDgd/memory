#pragma once
#include <memory/pooling/static/static_pool_type.h>
#include <memory/mman/mman_traits.h>

synapse_memory_pooling_static
synapse_memory_pooling_static_initialize
	(synapse_memory_mman_traits*, size_t, size_t);

void
synapse_memory_pooling_static_cleanup
	(synapse_memory_pooling_static);