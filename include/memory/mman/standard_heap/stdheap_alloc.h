#pragma once
#include <memory/mman/standard_heap/stdheap_type.h>

void*
synapse_memory_mman_stdheap_allocate
	(synapse_memory_mman_stdheap, void*, size_t);

void
synapse_memory_mman_stdheap_deallocate
	(synapse_memory_mman_stdheap, void*, size_t);

size_t
synapse_memory_mman_stdheap_alloc_unit
	(synapse_memory_mman_stdheap);