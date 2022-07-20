#include <structure/list/single_linked.h>
#include <structure/list/double_linked.h>

#include <synapse/memory/memory.h>
#include <synapse/memory/standard_heap.h>

#include <stdint.h>
#include <stddef.h>

typedef struct
    __synapse_memory_mman_nonpaged_block
{
    void*
        ptr_nonpaged;
    size_t
        sz_nonpaged;
} __synapse_memory_mman_nonpaged_block;

typedef struct
    __synapse_memory_mman_nonpaged
{
    synapse_structure_single_linked
        hnd_pooled;
    synapse_structure_double_linked
        hnd_pooled_page;
    size_t
        size_pooled_block;
    
    synapse_memory_manager*
        hnd_mman;
    synapse_memory_block
        hnd_mblock;
} __synapse_memory_mman_nonpaged;