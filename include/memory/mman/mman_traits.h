#pragma once
#include <memory/defines/opaque/opaque.h>

synapse_memory_opaque_declare
	(synapse_memory_mman_handle);

typedef struct synapse_memory_mman_traits
{
	synapse_memory_mman_handle
		hnd_mman;

	void*
		(*allocate)  (synapse_memory_mman_handle, void*, size_t);
	void
		(*deallocate)(synapse_memory_mman_handle, void*, size_t);
	size_t
		(*alloc_unit)(synapse_memory_mman_handle);
} synapse_memory_mman_traits;


#define synapse_memory_mman_traits_allocate(pMman, pHint, pSize)\
	pMman->allocate(pMman->hnd_mman, pHint, pSize)

#define synapse_memory_mman_traits_deallocate(pMman, pHint, pSize)\
	pMman->deallocate(pMman->hnd_mman, pHint, pSize)