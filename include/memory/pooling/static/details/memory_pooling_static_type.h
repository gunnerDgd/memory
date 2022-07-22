#pragma once
#include <memory/interface/memory_manager.h>

typedef struct
	__synapse_memory_pooling_static_block
{
	void* 
		blk_pointer;
	void* 
		blk_parent_pool;

	synapse_memory_block
		hnd_mblock_block_memory ;	
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
		__synapse_memory_pooling_static_block*
			hnd_pool_stack;

	synapse_memory_block
		ptr_pooled_mblock,
		ptr_mpool_mblock;
	void*
		ptr_pooled_memory;

} __synapse_memory_pooling_static;