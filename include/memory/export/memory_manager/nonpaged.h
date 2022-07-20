#pragma once
#include <memory/interface/memory_manager.h>
#include <memory/defines/export/export.h>

#include <memory/export/memory.h>

synapse_memory_dll
    synapse_memory_manager*
	    synapse_initialize_nonpaged
            (size_t);

synapse_memory_dll
    void
	    synapse_cleanup_nonpaged
		    (synapse_memory_manager*);