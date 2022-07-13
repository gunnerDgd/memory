#pragma once
#include <memory/defines/opaque/opaque.h>
#include <memory/interface/memory_manager.h>

#include <Windows.h>

typedef struct 
	__synapse_memory_pooling_dynamic_block
{
	SLIST_ENTRY
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
	SLIST_HEADER
		hnd_dynamic_stack;
	synapse_memory_manager*
		ptr_dynamic_mman;
	synapse_memory_block
		hnd_dynamic_mblock;

	size_t
		cnt_dynamic_pool,
		sz_dynamic_pool_block;
} __synapse_memory_pooling_dynamic;