#pragma once

#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

namespace memory {
    
    enum class file_map_mode : int
    {
        read    = PROT_READ ,
        write   = PROT_WRITE,
        execute = PROT_EXEC ,
        reserve = PROT_NONE
    };

    int operator| (file_map_mode l, file_map_mode r) { return (int)l | (int)r; }
    int operator& (file_map_mode l, file_map_mode r) { return (int)l & (int)r; }
    int operator^ (file_map_mode l, file_map_mode r) { return (int)l ^ (int)r; }

    class file_map_controller
    {
    public:
        using memory_size_t   = size_t;
        using memory_prot_t   = int   ;
        using memory_result_t = int   ;
        using file_handle_t   = int   ;

    public:
        static void*           allocate  (memory_size_t, void*, memory_prot_t, file_handle_t);
        static memory_result_t deallocate(memory_size_t, void*)               ;
        static memory_result_t control   (memory_size_t, void*, memory_prot_t);

        static memory_result_t lock      (memory_size_t, void*);
        static memory_result_t unlock    (memory_size_t, void*);
    };
}

void* memory::file_map_controller::allocate  (memory_size_t size, void* adjoin, memory_prot_t prot, file_handle_t hnd)
{
    return mmap  (adjoin, size, prot, MAP_PRIVATE | MAP_ANONYMOUS, hnd, 0);
}

typename memory::file_map_controller::memory_result_t memory::file_map_controller::deallocate(memory_size_t size, void* addr)
{
    return munmap(addr, size);
}

typename memory::file_map_controller::memory_result_t memory::file_map_controller::control(memory_size_t size, void* addr, memory_prot_t prot)
{
    return mprotect(addr, size, prot);
}

typename memory::file_map_controller::memory_result_t memory::file_map_controller::lock      (memory_size_t size, void* addr)
{
    return mlock(addr, size);
}

typename memory::file_map_controller::memory_result_t memory::file_map_controller::unlock    (memory_size_t size, void* addr)
{
    return munlock(addr, size);
}