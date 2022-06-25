#pragma once
#include <memory/mman/os_specific/winheap/details/memory_mman_winheap_type.h>

__synapse_memory_mman_winheap*
__synapse_memory_mman_winheap_initialize
	(size_t, size_t);

void
__synapse_memory_mman_winheap_cleanup
	(__synapse_memory_mman_winheap*);