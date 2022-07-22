#pragma once
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_type.h>

__synapse_memory_pooling_dynamic*
	__synapse_memory_pooling_dynamic_initialize	
		(synapse_memory_manager*, size_t, size_t);

__synapse_memory_pooling_dynamic_block*
	__synapse_memory_pooling_dynamic_block_initialize
		(__synapse_memory_pooling_dynamic*);

void
	__synapse_memory_pooling_dynamic_cleanup
		(__synapse_memory_pooling_dynamic*);

void
	__synapse_memory_pooling_dynamic_block_cleanup
		(__synapse_memory_pooling_dynamic*,
		 __synapse_memory_pooling_dynamic_block*);