#pragma once
#include <memory/defines/opaque/opaque.h>
#include <memory/interface/memory_manager.h>

typedef struct 
	__synapse_memory_pooling_dynamic_block
{
	void*
		ptr_pooled_memory;
	void*
		ptr_parent_pool;
	
	synapse_memory_block
		mblock_block_pooled_memory;
	
	volatile
		struct 
			__synapse_memory_pooling_dynamic_block
				*ptr_next;
} __synapse_memory_pooling_dynamic_block;

typedef struct 
	__synapse_memory_pooling_dynamic
{
	volatile
		__synapse_memory_pooling_dynamic_block
			*ptr_dynamic_pool_stack;
			
	synapse_memory_manager*
		ptr_dynamic_mman;

	volatile size_t
		count_dynamic_pool;
	size_t
		size_dynamic_pool_block;
} __synapse_memory_pooling_dynamic;