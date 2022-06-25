#pragma once
#include <memory/pooling/static/details/memory_pooling_static_type.h>

__synapse_memory_pooling_static_chunk*
__synapse_memory_pooling_static_allocate
	(__synapse_memory_pooling_static*);

void*
__synapse_memory_pooling_static_deallocate
	(__synapse_memory_pooling_static*, __synapse_memory_pooling_static_chunk*);