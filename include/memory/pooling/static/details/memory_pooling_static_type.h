#pragma once
#include <memory/interface/memory_manager.h>

typedef struct
	__synapse_memory_pooling_static_block
{
	void* 
		blk_pointer;
	void* 
		blk_parent_pool;

	volatile
		struct __synapse_memory_pooling_static_block*
			ptr_next;
} __synapse_memory_pooling_static_block;

typedef struct
	__synapse_memory_pooling_static
{
	synapse_memory_manager*
		ptr_pool_mman;
	volatile
		__synapse_memory_pooling_static_block
			*ptr_pool_block_stack,
			*ptr_pool_block;

	void*
		ptr_pooled;

} __synapse_memory_pooling_static;