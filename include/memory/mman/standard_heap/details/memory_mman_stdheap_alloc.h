#pragma once
#include <memory/mman/standard_heap/details/memory_mman_stdheap_type.h>

__synapse_memory_mman_stdheap*
__synapse_memory_mman_stdheap_allocate
	(__synapse_memory_mman_stdheap_head*, void*, size_t);

void
__synapse_memory_mman_stdheap_deallocate
	(__synapse_memory_mman_stdheap_head*, __synapse_memory_mman_stdheap*);

void
__synapse_memory_mman_stdheap_deallocate_all
	(__synapse_memory_mman_stdheap_head*);