#pragma once
#include <stdint.h>
#include <memory/defines/export/export.h>

synapse_memory_dll
void*
	synapse_system_allocate
		(size_t);

synapse_memory_dll
void
	synapse_system_deallocate
		(void*);