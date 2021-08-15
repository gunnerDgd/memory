#pragma once

#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

namespace memory {

    enum  vmem_mode : int
    {
        read    = PROT_READ ,
        write   = PROT_WRITE,
        execute = PROT_EXEC 
    };

    int operator| (vmem_mode l, vmem_mode r) { return (int)l | (int)r; }
    int operator& (vmem_mode l, vmem_mode r) { return (int)l & (int)r; }
    int operator^ (vmem_mode l, vmem_mode r) { return (int)l ^ (int)r; }

    class vmem_controller
    {
    public:
        using memory_size_t   = size_t;
        using memory_prot_t   = int   ;
        using memory_result_t = int   ;

    public:
        static void*           allocate  (memory_size_t, void*, memory_prot_t);
        static memory_result_t deallocate(memory_size_t, void*);
    };
    
    class rmem_controller
    {
    public:
        using memory_size_t   = size_t;
        using memory_prot_t   = int   ;
        using memory_result_t = int   ;

    public:
        static void*           allocate  (memory_size_t, void*);
        static memory_result_t deallocate(memory_size_t, void*);
    };
}

void* memory::vmem_controller::allocate  (memory_size_t size, void* adjoin, memory_prot_t prot)
{
    return mmap  (adjoin, size, prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

typename memory::vmem_controller::memory_result_t memory::vmem_controller::deallocate(memory_size_t size, void* addr)
{
    return munmap(addr, size);
}

void* memory::rmem_controller::allocate  (memory_size_t size, void* adjoin)
{
    return mmap  (adjoin, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

typename memory::rmem_controller::memory_result_t memory::rmem_controller::deallocate(memory_size_t size, void* addr)
{
    return munmap(addr, size);
}