#pragma once
#include <memory/defines/opaque/opaque.h>

synapse_memory_opaque_declare
	(synapse_memory_manager_handle);

typedef struct synapse_memory_manager
{
	synapse_memory_manager_handle
		hnd_mman;

	void*
		(*allocate)
			(synapse_memory_manager_handle, void*, size_t);
	void
		(*deallocate)
			(synapse_memory_manager_handle, void*);
	void
		(*deallocate_all)
			(synapse_memory_manager_handle);
} synapse_memory_manager;