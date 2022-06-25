#pragma once
#include <memory/mman/standard_heap/details/memory_mman_stdheap_type.h>

void*
__synapse_memory_mman_stdheap_allocate
	(__synapse_memory_mman_stdheap*, void*, size_t);

void
__synapse_memory_mman_stdheap_deallocate
	(__synapse_memory_mman_stdheap*, void*, size_t);

size_t
__synapse_memory_mman_stdheap_alloc_unit
	(__synapse_memory_mman_stdheap*);