#pragma once
#include <stdint.h>

#define synapse_memory_opaque_declare(pName)\
	typedef struct pName { void* opaque; } pName;

#define synapse_memory_opaque_reference(pObject)\
	(pObject.opaque)

#define synapse_memory_opaque_cast(pObject, pType)\
	((pType)(pObject.opaque))

#define synapse_memory_opaque_init(pType, pName, pValue)\
	pType pName = { .opaque = pValue }

#define synapse_memory_opaque_valid(pObject)\
	(pObject.opaque != NULL)