#pragma once
#include <memory/memory.hpp>

namespace memory {
    class reserved : public memory
    {
    public:
        reserved     (void* r_address = nullptr)
            :  memory(nullptr, 4096)
        {
            memory_address    = mmap(r_address, 4096, protect_type::reserve, 
                                     MAP_PRIVATE | MAP_ANONYMOUS           , -1, 0);
            memory_protection = protect_type::reserve;
        }
    };
}