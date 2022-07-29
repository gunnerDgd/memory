#pragma once
#include <memory/interface/memory_manager.h>

#include <stdint.h>
#include <stddef.h>

typedef struct
    __synapse_memory_mman_nonpaged_page
{
    void*
        ptr_alloc_page;
    volatile struct
        __synapse_memory_mman_nonpaged_page*
            ptr_next;
} __synapse_memory_mman_nonpaged_page;

typedef struct
    __synapse_memory_mman_nonpaged_block
{
    void*
        ptr_nonpaged_parent;
    volatile struct
        __synapse_memory_mman_nonpaged_block*
            ptr_next_block;
} __synapse_memory_mman_nonpaged_block;

typedef struct
    __synapse_memory_mman_nonpaged_bucket
{
    volatile
        __synapse_memory_mman_nonpaged_block*
            ptr_bucket_block;
} __synapse_memory_mman_nonpaged_bucket;

typedef struct
    __synapse_memory_mman_nonpaged
{
    __synapse_memory_mman_nonpaged_bucket
            hnd_pooled[5];
    volatile
        __synapse_memory_mman_nonpaged_page*
            hnd_pooled_page;
} __synapse_memory_mman_nonpaged;

#define __synapse_memory_mman_nonpaged_page_size 4096