#pragma once
#include <memory/interface/memory_manager.h>

void*
	synapse_memory_mman_stdheap_allocate
		(synapse_memory_manager_handle, void*, size_t);

void
	synapse_memory_mman_stdheap_deallocate
		(synapse_memory_manager_handle, void*);

void
	synapse_memory_mman_stdheap_deallocate_all
		(synapse_memory_manager_handle);