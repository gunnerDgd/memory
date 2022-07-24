#pragma once
#include <stdint.h>
#include <stdbool.h>

#include <memory/defines/export/export.h>

#include <memory/interface/memory_manager.h>
#include <memory/interface/memory_pooling.h>

synapse_memory_dll
	synapse_memory_manager*
		synapse_system_memory_manager();

synapse_memory_dll
	void*
		synapse_system_allocate
			(size_t);

synapse_memory_dll
	void
		synapse_system_deallocate
			(void*);

synapse_memory_dll
	void*
		synapse_system_aligned_allocate
			(size_t, size_t);

synapse_memory_dll
	void
		synapse_system_aligned_deallocate
			(void*);

synapse_memory_dll
	void*
		synapse_system_allocate_page
			(void*, size_t);

synapse_memory_dll
	void
		synapse_system_deallocate_page
			(void*, size_t);

synapse_memory_dll
	bool
		synapse_query_paging_support
			();

synapse_memory_dll
	size_t
		synapse_query_system_page_size
			();

synapse_memory_dll
	bool
		synapse_query_aligned_allocation_support
			();