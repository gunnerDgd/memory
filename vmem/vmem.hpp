#pragma once

#include <memory/vmem/vmem_reserve.hpp>
#include <memory/memory_attr.hpp>

#ifdef ENVIORMENT_UNIX
#include <sys/mman.h>
#elif ENVIORMENT_WINDOWS
#include <Memoryapi.h>
#endif

namespace memory  {
    class vmem    : public memory::memory
    {
    public:
        vmem(memory_protect_t vm_protect , void*            vm_addr    = nullptr);
        vmem(reserved&        vm_reserved, memory_protect_t vm_protect = protect_type::read | protect_type::write);

        vmem(vmem&  copy_vmem);
        vmem(vmem&& move_vmem);
        
        ~vmem();
    };
}

memory::vmem::vmem(memory_protect_t vm_protect, void* vm_addr)
          : memory(nullptr, 4096, vm_protect)
{

    memory_address     = mmap(vm_addr, memory_block_size , vm_protect,
                              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)    ;
    
    if(!memory_address && !vm_addr) // If Memory Allocation Failed.
        memory_address = mmap(nullptr, memory_block_size , vm_protect,
                              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)    ;
    
    if(!memory_address)
    {
        VMEM_HANDLE_MMAP_FAILED(*this, "Lack Of Virtual Memory Space");
        exit                   (2);
    }
}

memory::vmem::vmem(vmem& copy_vmem)
          : memory(copy_vmem)
{ 
    memory_address    = mmap(nullptr, 4096, memory_protection, 
                             MAP_PRIVATE | MAP_ANONYMOUS     , -1, 0);

    if(!memory_address) VMEM_HANDLE_MMAP_FAILED(*this, "Lack Of Virtual Memory Space");
}

memory::vmem::vmem(vmem&&    move_vmem)
          : memory(std::move(move_vmem))
{
    move_vmem.memory_address    = nullptr;
    move_vmem.memory_block_size = 0      ;
}

memory::vmem::~vmem()
{
    int um_res =    munmap(memory_address, memory_block_size);
    if (um_res < 0) VMEM_HANDLE_MNUMAP_FAILED;
}

memory::vmem::vmem(reserved& vm_reserved, memory_protect_t vm_protect)
    : memory      (std::move(vm_reserved))
{
    int c_res     = mprotect(memory_address, 4096, vm_protect);
    if (c_res != 0) VMEM_HANDLE_MPROTECT_FAILED(*this)        ;
}