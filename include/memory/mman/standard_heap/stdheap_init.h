#pragma once
#include <synapse/memory/interface/memory_manager.h>

synapse_memory_manager_handle
	synapse_memory_mman_stdheap_initialize
		();

void
	synapse_memory_mman_stdheap_cleanup
		(synapse_memory_manager_handle);