#include <memory/system/support/system_support.h>

bool
    synapse_memory_query_paging_support
        ()
{
    return true;
}

// Returns True If System Supports Hardware / Software Based Page Lock.
bool
    synapse_memory_query_page_lock_support
        ()
{
    return true;
}

size_t
    synapse_memory_query_page_size
        ()
{
    return 4096;
}

bool
    synapse_memory_query_aligned_allocation
        ()
{
    return true;
}