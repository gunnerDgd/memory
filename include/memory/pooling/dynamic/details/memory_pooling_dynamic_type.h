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
		mblock_block_pooled,
		mblock_block_memory;
	
	volatile
		struct 
			__synapse_memory_pooling_dynamic_block
				*ptr_next;
} __synapse_memory_pooling_dynamic_block;

typedef struct 
	__synapse_memory_pooling_dynamic
{
	volatile
		__synapse_memory_pooling_dynamic_block*
			hnd_dynamic_stack;
	synapse_memory_manager*
		ptr_dynamic_mman;
	synapse_memory_block
		hnd_dynamic_mblock;

	volatile size_t
		dynamic_pool_count;
	size_t
		dynamic_pool_block_size;
} __synapse_memory_pooling_dynamic;