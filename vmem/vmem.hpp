#pragma once

#include <memory/memory.hpp>
#include <memory/memory_attr.hpp>

#include <sys/mman.h>

namespace memory  {
    class vmem    : public memory::memory
    {
    public:
        vmem (uint64_t vm_page_count = 1,
              int      vm_protect    = protect_type::read | protect_type::write,
              void*    vm_addr       = nullptr);

        vmem(memory::vmem& copy_vmem)
        { 
            memory_block_size      = copy_vmem.memory_block_size     ;
            memory_state_flag      = copy_vmem.memory_state_flag     ;
            memory_address         = copy_vmem.memory_address        ;
            memory_reference_count = copy_vmem.memory_reference_count;
            
            ++(*memory_reference_count); 
        }

        vmem(memory::vmem&& copy_vmem)
        { 
            memory_block_size        = copy_vmem.memory_block_size     ;
            memory_state_flag        = copy_vmem.memory_state_flag     ;
            memory_address           = copy_vmem.memory_address        ;
            memory_reference_count   = copy_vmem.memory_reference_count;
            
            copy_vmem.memory_address = nullptr;
        }

        ~vmem();
    };
}
}

memory::vmem::vmem(uint64_t vm_page_count, int vm_protect, void* vm_addr)
    : memory(nullptr, vm_page_count * 4096)
{
    memory_address = mmap(vm_addr                    , 
                          memory_block_size          ,
                          vm_protect                 ,
                          MAP_PRIVATE | MAP_ANONYMOUS,
                          -1                         ,
                          0
                         );

    memory_reference_count  = new uint64_t;
    *memory_reference_count = 1;

    if(!memory_address) // If Memory Allocation Failed.
        memory_state_flag = memory::memory_state::allocate_error;    
}

memory::vmem::~vmem()
{
    if(*memory_reference_count > 1)
        return;

    int um_res = munmap(memory_address, memory_block_size);
    if (um_res < 0 && memory_state_flag == memory::memory_state::normal)
    {
        std::cerr << "FATAL ## MUNMAP Failed...\n";
        exit(1);
    }
}