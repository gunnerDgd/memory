#pragma once
#include <memory/mman/standard_heap/details/memory_mman_stdheap_type.h>

__synapse_memory_mman_stdheap*
__synapse_memory_mman_stdheap_initialize
	(size_t);

void
__synapse_memory_mman_stdheap_cleanup
	(__synapse_memory_mman_stdheap*);