#pragma once

#include <iostream>
#include <memory/memory_attr.hpp>

namespace memory  {
    class memory
    {
    public:
        memory(void*  mem_addr = nullptr, 
               size_t mem_size = 0)
            : memory_block_size     (mem_size),
              memory_address        (mem_addr),
              memory_state_flag     (synapse::memory::memory_state::normal),
              memory_reference_count(new uint64_t)                         { *memory_reference_count = 1; }

        ~memory()
        {
            --(*memory_reference_count);
            if(*memory_reference_count == 0)
                delete memory_reference_count;
        }

        memory                    (memory::memory&  copy_memory);
        memory                    (memory::memory&& move_memory);
        memory::memory& operator= (memory::memory&  copy_memory);

        void*  memory_pointer () { return  memory_address   ;      }
        size_t memory_size    () { return  memory_block_size;      }
        size_t reference_count() { return *memory_reference_count; }

        memory::memory_state current_state()                        { return memory_state_flag; }
        void                 set_state    (memory::memory_state& s) { memory_state_flag = s   ; }

    protected:
        synapse::memory::memory_state     memory_state_flag     ;
        size_t                            memory_block_size     ;
        void*                             memory_address        ;
        uint64_t                         *memory_reference_count;
    };
}
}

memory::memory::memory(memory::memory&  copy_memory)
    : memory_state_flag     (copy_memory.memory_state_flag),
      memory_block_size     (copy_memory.memory_block_size),
      memory_address        (copy_memory.memory_address),
      memory_reference_count(copy_memory.memory_reference_count) { ++(*memory_reference_count); }

memory::memory::memory(memory::memory&& move_memory)
    : memory_state_flag     (move_memory.memory_state_flag),
      memory_block_size     (move_memory.memory_block_size),
      memory_address        (move_memory.memory_address),
      memory_reference_count(move_memory.memory_reference_count)
{
    move_memory.memory_block_size      = 0;
    move_memory.memory_address         = nullptr;
    move_memory.memory_reference_count = new uint64_t;
}

memory::memory& memory::memory::operator= (memory::memory&  copy_memory)
{
    memory_state_flag      = copy_memory.memory_state_flag;
    memory_block_size      = copy_memory.memory_block_size;
    memory_address         = copy_memory.memory_address   ;
    memory_reference_count = copy_memory.memory_reference_count;
    
    ++(*memory_reference_count);
    return *this;
}