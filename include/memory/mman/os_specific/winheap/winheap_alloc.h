#pragma once
#include <memory/mman/os_specific/winheap/winheap_type.h>

void*
synapse_memory_mman_winheap_allocate
	(synapse_memory_mman_winheap, void*, size_t);

void
synapse_memory_mman_winheap_deallocate
	(synapse_memory_mman_winheap, void*, size_t);