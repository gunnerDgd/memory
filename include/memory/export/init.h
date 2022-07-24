// For Internal Use.
#include <memory/defines/export/export.h>

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#define SYNAPSE_MEMORY_SYSTEM_STANDARD_HEAP_MODE 0
#define SYNAPSE_MEMORY_SYSTEM_NONPAGED_POOL_MODE 1

synapse_memory_dll
    void
	    synapse_memory_initialize_system
		    (uint16_t);

synapse_memory_dll
    void
	    synapse_memory_cleanup_system
		    ();