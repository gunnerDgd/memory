#pragma once

#include <iostream>
#include <memory/memory_attr.hpp>

namespace memory  {
    class memory
    {
    public:
        memory(void*            mem_addr    = nullptr, 
               size_t           mem_size    = 0,
               memory_protect_t mem_protect = protect_type::read | protect_type::write)
            : memory_block_size(mem_size)            ,
              memory_address   (mem_addr)            ,
              memory_state_flag(memory_state::normal),
              memory_protection(mem_protect)         {  }
        ~memory()                                    {  }

        memory                    (memory&  copy_memory);
        memory                    (memory&& move_memory);
        memory& operator=         (memory&  copy_memory);

        void*  memory_pointer     ()                { return  memory_address   ; }
        size_t memory_size        ()                { return  memory_block_size; }

        memory_state     get_state()                { return memory_state_flag; }
        void             set_state(memory_state s)  { memory_state_flag = s   ; }
        memory_protect_t get_protection_state()     { return memory_protection; }

    protected:
        memory_state     memory_state_flag;
        memory_protect_t memory_protection;

        size_t           memory_block_size;
        void*            memory_address   ;
    };
}

memory::memory::memory(memory&  copy_memory)
    : memory_state_flag(copy_memory.memory_state_flag),
      memory_block_size(copy_memory.memory_block_size),
      memory_protection(copy_memory.memory_protection) {  }

memory::memory::memory(memory&& move_memory)
    : memory_state_flag(move_memory.memory_state_flag),
      memory_protection(move_memory.memory_protection),
      memory_block_size(move_memory.memory_block_size),
      memory_address   (move_memory.memory_address)    {  }

memory::memory& memory::memory::operator= (memory&  copy_memory)
{
    memory_state_flag      = copy_memory.memory_state_flag;
    memory_block_size      = copy_memory.memory_block_size;
    memory_address         = copy_memory.memory_address   ;
    
    return *this;
}