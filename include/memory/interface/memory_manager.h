#pragma once
#include <memory/defines/opaque/opaque.h>

synapse_memory_opaque_declare
	(synapse_memory_manager_handle);

synapse_memory_opaque_declare
	(synapse_memory_block);

typedef struct synapse_memory_manager
{
	synapse_memory_manager_handle
		hnd_mman;

	synapse_memory_block
		(*allocate)
			(synapse_memory_manager_handle, void*, size_t);
	void
		(*deallocate)
			(synapse_memory_manager_handle, synapse_memory_block);
	void
		(*deallocate_all)
			(synapse_memory_manager_handle);

	void*
		(*block_pointer)
			(synapse_memory_block);
	size_t
		(*block_size)
			(synapse_memory_block);
} synapse_memory_manager;


#define synapse_memory_mman_traits_allocate(pMman, pHint, pSize)\
	pMman->allocate(pMman->hnd_mman, pHint, pSize)

#define synapse_memory_mman_traits_deallocate(pMman, pHint, pSize)\
	pMman->deallocate(pMman->hnd_mman, pHint, pSize)