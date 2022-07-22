#include <memory/interface/memory_manager.h>

#include <stdint.h>
#include <stddef.h>

#define __synapse_nonpaged_bucket_count     5
#define __synapse_nonpaged_bucket_page_size 4096

typedef struct
    __synapse_memory_mman_nonpaged_bucket
{
    void*
        ptr_nonpaged;
    void*
        ptr_parent_pool;
    uint8_t
        idx_nonpaged_index;
    volatile
        struct __synapse_memory_mman_nonpaged_bucket*
            ptr_next;
} __synapse_memory_mman_nonpaged_bucket;

typedef struct
    __synapse_memory_mman_nonpaged_bucket_page
{
    void*
        ptr_page;
    struct
        __synapse_memory_mman_nonpaged_page*
            ptr_next;
} __synapse_memory_mman_nonpaged_bucket_page;



/*
    0 : 32 Byte
    1 : 64 Byte
    2 : 128 Byte
    3 : 256 Byte
    4 : 512 Byte
*/

typedef struct
    __synapse_memory_mman_nonpaged
{
    volatile
        __synapse_memory_mman_nonpaged_bucket*
            hnd_pooled
                [__synapse_nonpaged_bucket_count];
    
    volatile
        __synapse_memory_mman_nonpaged_bucket_page*
            hnd_pooled_page
                [__synapse_nonpaged_bucket_count];
} __synapse_memory_mman_nonpaged;