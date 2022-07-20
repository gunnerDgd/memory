#pragma once
#include <memory/defines/opaque/opaque.h>
#include <memory/interface/memory_manager.h>

#include <structure/list/single_linked.h>

typedef struct 
	__synapse_memory_pooling_dynamic_block
{
	synapse_structure_single_linked_node
		hnd_slist;
	void*
		ptr_block_mpool ;
	void*
		ptr_block_memory;
	synapse_memory_block
		ptr_block_mblock;
} __synapse_memory_pooling_dynamic_block;

typedef struct 
	__synapse_memory_pooling_dynamic
{
	synapse_structure_single_linked
		hnd_dynamic_stack;
	synapse_memory_manager*
		ptr_dynamic_mman;
	synapse_memory_block
		hnd_dynamic_mblock;

	size_t
		dynamic_pool_count,
		dynamic_pool_block_size;
} __synapse_memory_pooling_dynamic;