#pragma once
#include <memory/mman/mman_traits.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_type.h>

__synapse_memory_pooling_dynamic_chunk*
__synapse_memory_pooling_dynamic_allocate
	(__synapse_memory_pooling_dynamic*, void*);

void
__synapse_memory_pooling_dynamic_deallocate
	(__synapse_memory_pooling_dynamic*, __synapse_memory_pooling_dynamic_chunk*);

size_t
__synapse_memory_pooling_dynamic_expand
	(__synapse_memory_pooling_dynamic*, size_t);

size_t
__synapse_memory_pooling_dynamic_shrink
	(__synapse_memory_pooling_dynamic*, size_t);

size_t
__synapse_memory_pooling_dynamic_current_size
	(__synapse_memory_pooling_dynamic*);