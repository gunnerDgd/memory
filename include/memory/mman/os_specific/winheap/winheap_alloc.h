#pragma once


void*
	synapse_memory_mman_winheap_allocate
		(synapse_memory_mman_winheap, void*, size_t);

void
synapse_memory_mman_winheap_deallocate
	(synapse_memory_mman_winheap, void*, size_t);