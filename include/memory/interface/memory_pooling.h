#pragma once
#include <memory/defines/opaque/opaque.h>

synapse_memory_opaque_declare
	(synapse_memory_pool_handle);

typedef struct
	synapse_memory_static_pool
{
	synapse_memory_pool_handle
		hnd_static_pool;

	void*
		(*allocate)  
			(synapse_memory_pool_handle);
	void*
		(*allocate_until_success)
			(synapse_memory_pool_handle);
	void
		(*deallocate)
			(synapse_memory_pool_handle, void*);

} synapse_memory_static_pool;

typedef struct
	synapse_memory_dynamic_pool
{
	synapse_memory_pool_handle
		hnd_dynamic_pool;

	void*
		(*allocate)
			(synapse_memory_pool_handle);
	void*
		(*allocate_until_success)
			(synapse_memory_pool_handle);
	void
		(*deallocate)
			(synapse_memory_pool_handle, void*);
	void
		(*reserve)
			(synapse_memory_pool_handle, size_t);
} synapse_memory_dynamic_pool;