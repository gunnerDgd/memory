#pragma once
#include <memory/defines/opaque/opaque.h>

synapse_memory_opaque_declare
	(synapse_memory_pooling_static_handle)

synapse_memory_opaque_declare
	(synapse_memory_pooling_static_chunk)

typedef struct
	synapse_memory_pooling_static_traits
{
	synapse_memory_pooling_static_handle
		hnd_traits;

	synapse_memory_pooling_static_chunk
		(*allocate)  (synapse_memory_pooling_static_handle, void*);
	void
		(*deallocate)(synapse_memory_pooling_static_handle, void*);
	void*
		(*retrieve_pointer)(synapse_memory_pooling_static_chunk);
	
} synapse_memory_pooling_static_traits;

#define synapse_memory_pooling_static_traits_allocate(pObj, pHint, pCount)\
	pObj->allocate(pObj->hnd_traits, pHint, pCount)

#define synapse_memory_pooling_static_traits_deallocate(pObj, pHint, pCount)\
	pObj->deallocate(pObj->hnd_traits, pHint, pCount)

#define synapse_memory_pooling_static_tratis_retrieve_pointer(pObj, pChunk)\
	pObj->retrieve_pointer(pChunk)