#pragma once
#include <memory/interface/memory_pooling.h>

void*
	synapse_memory_pooling_static_allocate
		(synapse_memory_pool_handle);

void*
	synapse_memory_pooling_static_allocate_until_success
		(synapse_memory_pool_handle);
		
void
	synapse_memory_pooling_static_deallocate
		(synapse_memory_pool_handle, void*);