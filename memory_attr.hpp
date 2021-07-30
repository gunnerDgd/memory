#pragma once
#include <sys/mman.h>

namespace memory  {
    using memory_protect_t = int;
    enum  protect_type     : int
    {
        read    = PROT_READ ,
        write   = PROT_WRITE,
        execute = PROT_EXEC ,
        reserve = PROT_NONE
    };

    int operator| (const protect_type& lhs, const protect_type& rhs) { return (int)lhs | (int)rhs; }
    int operator| (const protect_type& lhs, const int& rhs)          { return (int)lhs | rhs;      }

    enum lock_type     : bool { locked, unlocked };
    enum memory_state  : int
    {
        normal          ,
        allocate_error  ,
        deallocate_error
    };

    enum io_map_state  : int
    {
        mapped,
        unmapped
    };

    enum vmem_allocate_type : uint64_t // For Huge Page Support.
    {
        standard = 4096,              // 4KB Size,
        medium   = 1024 * 1024 * 2,   // 2MB Size,
        large    = 1024 * 1024 * 1024 // 1GB Size.
    };
}