#pragma once
#include <memory/mman/os_specific/winheap/winheap_type.h>

synapse_memory_mman_winheap
synapse_memory_mman_winheap_initialize
	(size_t, size_t);

void
synapse_memory_mman_winheap_cleanup
	(synapse_memory_mman_winheap);