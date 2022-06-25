#pragma once
#include <memory/mman/mman_traits.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_type.h>

__synapse_memory_pooling_dynamic*
__synapse_memory_pooling_dynamic_initialize	
	(synapse_memory_mman_traits*, size_t, size_t);

void
__synapse_memory_pooling_dynamic_cleanup
	(__synapse_memory_pooling_dynamic*);