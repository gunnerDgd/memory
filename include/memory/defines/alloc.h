#pragma once

#define synapse_memory_default_alloc(pHint, pSize)\
			malloc(pSize)

#define synapse_memory_default_dealloc(pDealloc, pSize)\
			free(pDealloc)