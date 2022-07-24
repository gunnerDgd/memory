#include <stdint.h>
#include <stddef.h>

#include <stdbool.h>

// Returns True If System Supports Hardware / Software Based Paging.
bool
    synapse_memory_query_paging_support
        ();

// Returns True If System Supports Hardware / Software Based Page Lock.
bool
    synapse_memory_query_page_lock_support
        ();

size_t
    synapse_memory_query_page_size
        ();

bool
    synapse_memory_query_aligned_allocation
        ();