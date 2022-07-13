#pragma once
#include <stdint.h>
#include <memory/defines/export/export.h>

#include <memory/interface/memory_manager.h>
#include <memory/interface/memory_pooling.h>

synapse_memory_dll
	synapse_memory_block
		synapse_memory_allocate_from_system
			(size_t);

synapse_memory_dll
	void
		synapse_memory_deallocate_from_system
			(synapse_memory_block);