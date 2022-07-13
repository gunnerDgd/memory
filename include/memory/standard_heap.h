#pragma once
#include <memory/interface/memory_manager.h>
#include <memory/defines/export/export.h>

synapse_memory_dll
synapse_memory_manager*
	synapse_initialize_standard_heap();

synapse_memory_dll
void
	synapse_cleanup_standard_heap
		(synapse_memory_manager*);