#pragma once
#include <memory/pooling/static/details/memory_pooling_static_type.h>

__synapse_memory_pooling_static*
	__synapse_memory_pooling_static_initialize
		(synapse_memory_manager*, size_t, size_t);

void
	__synapse_memory_pooling_static_cleanup
		(__synapse_memory_pooling_static*);