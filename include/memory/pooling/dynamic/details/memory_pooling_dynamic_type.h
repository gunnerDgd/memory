#pragma once
#include <memory/defines/opaque/opaque.h>
#include <memory/mman/mman_traits.h>

#include <Windows.h>

typedef struct __synapse_memory_pooling_dynamic_chunk
{
	SLIST_ENTRY
		hnd_slist;
	void*
		ptr_chunk;
} __synapse_memory_pooling_dynamic_chunk;

typedef struct __synapse_memory_pooling_dynamic
{
	SLIST_HEADER
		hnd_dynamic_stack;
	synapse_memory_mman_traits*
		ptr_dynamic_mman;

	void*
		ptr_dynamic_stack;
	size_t
		sz_dynamic_stack_chunk;
} __synapse_memory_pooling_dynamic;