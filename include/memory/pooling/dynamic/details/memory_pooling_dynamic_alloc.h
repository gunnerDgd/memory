#pragma once
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_type.h>

void*
	__synapse_memory_pooling_dynamic_allocate
		(__synapse_memory_pooling_dynamic*);

void
	__synapse_memory_pooling_dynamic_deallocate
		(__synapse_memory_pooling_dynamic*, __synapse_memory_pooling_dynamic_block*);

size_t
	__synapse_memory_pooling_dynamic_reserve
		(__synapse_memory_pooling_dynamic*, size_t);