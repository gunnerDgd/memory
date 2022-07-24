#pragma once
#include <memory/interface/memory_manager.h>

synapse_memory_manager_handle
	synapse_memory_mman_stdheap_initialize
		();

synapse_memory_manager*
	synapse_memory_mman_stdheap_initialize_memory_manager
		();

void
	synapse_memory_mman_stdheap_cleanup
		(synapse_memory_manager_handle);

void
	synapse_memory_mman_stdheap_cleanup_memory_manager
		(synapse_memory_manager*);