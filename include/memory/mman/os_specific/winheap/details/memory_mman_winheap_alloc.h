#pragma once
#include <memory/mman/os_specific/winheap/details/memory_mman_winheap_type.h>

void*
__synapse_memory_mman_winheap_allocate
	(__synapse_memory_mman_winheap*, size_t);

void
__synapse_memory_mman_winheap_deallocate
	(__synapse_memory_mman_winheap*, void*);