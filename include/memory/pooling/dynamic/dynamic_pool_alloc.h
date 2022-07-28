#pragma once
#include <memory/interface/memory_pooling.h>

void*
	synapse_memory_pooling_dynamic_allocate
		(synapse_memory_pool_handle);

void*
	synapse_memory_pooling_dynamic_allocate_until_success
		(synapse_memory_pool_handle);

void
	synapse_memory_pooling_dynamic_deallocate
		(synapse_memory_pool_handle, void*);

size_t
	synapse_memory_pooling_dynamic_reserve
		(synapse_memory_pool_handle, size_t);