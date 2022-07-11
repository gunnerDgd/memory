#pragma once
#include <stdlib.h>

typedef struct 
	__synapse_memory_mman_stdheap
{
	void*
		stdheap_ptr;
	size_t
		stdheap_size;
	void*
		stdheap_alloc_head;

	struct __synapse_memory_mman_stdheap
		*stdheap_next,
		*stdheap_prev;
} __synapse_memory_mman_stdheap;

typedef struct
	__synapse_memory_mman_stdheap_head
{
	__synapse_memory_mman_stdheap
		* ptr_head,
		* ptr_back;
} __synapse_memory_mman_stdheap_head;