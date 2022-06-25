#pragma once
#include <memory/mman/mman_traits.h>
#include <Windows.h>

typedef struct
	__synapse_memory_pooling_static_chunk
{
	SLIST_ENTRY chk_slist_hnd;
	void*		chk_ptr;
} __synapse_memory_pooling_static_chunk;

typedef struct
	__synapse_memory_pooling_static
{
	synapse_memory_mman_traits*
		ptr_pool_mman;
	SLIST_HEADER
		hnd_pool_stack;

	void*
		ptr_pooled_memory;
	size_t
		sz_pooled_chunk		 ,
		sz_pooled_chunk_count;

	size_t
		ptr_pooled_memory_begin,
		ptr_pooled_memory_end  ;
} __synapse_memory_pooling_static;