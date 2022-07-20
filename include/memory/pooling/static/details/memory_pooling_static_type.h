#pragma once
#include <memory/interface/memory_manager.h>
#include <structure/list/single_linked.h>

typedef struct
	__synapse_memory_pooling_static_block
{
	synapse_structure_single_linked_node
				blk_handle;
	void*		blk_pointer;
	void*		blk_pool   ;
} __synapse_memory_pooling_static_block;

typedef struct
	__synapse_memory_pooling_static
{
	synapse_memory_manager*
		ptr_pool_mman;
	synapse_structure_single_linked
		hnd_pool_stack;

	synapse_memory_block
		ptr_pooled_mblock,
		ptr_mpool_mblock;
	void*
		ptr_pooled_memory;

} __synapse_memory_pooling_static;