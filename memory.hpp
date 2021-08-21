#pragma once
#include <tuple>
#include <type_traits>

namespace memory {

    template <typename memory_data_t, typename memory_controller_t>
    class virtual_memory;

    template <typename memory_data_t, typename memory_controller_t>
    class virtual_memory
    {
    public:
        using size_type     = typename memory_controller_t::memory_size_t  ;
        using result_type   = typename memory_controller_t::memory_result_t;
        using prot_type     = typename memory_controller_t::memory_prot_t  ;

        using block_type    = std::conditional_t<std::is_array_v     <memory_data_t>,
                                                 std::remove_extent_t<memory_data_t>,
                                                                      memory_data_t>;
        using pointer_type  = std::add_pointer_t<block_type>;
        
    public:
        template <typename... Args>
        virtual_memory (void* vm_adjoin, Args... vm_args);
        template <typename... Args>
        virtual_memory (Args... vm_args);
        ~virtual_memory();
    
    public:
        pointer_type get_pointer () { return memory_pointer; }

    protected:
        pointer_type memory_pointer;
    };
}

template <typename memory_data_t, typename memory_controller_t>
template <typename... Args>
memory::virtual_memory<memory_data_t, memory_controller_t>::virtual_memory(void* vm_adjoin, Args... vm_args)
    : memory_pointer((pointer_type)memory_controller_t::allocate(sizeof(memory_data_t), vm_adjoin, std::forward<Args>(vm_args)...)) { }

template <typename memory_data_t, typename memory_controller_t>
template <typename... Args>
memory::virtual_memory<memory_data_t, memory_controller_t>::virtual_memory (Args... vm_args)
    : memory_pointer((pointer_type)memory_controller_t::allocate(sizeof(memory_data_t), nullptr, std::forward<Args>(vm_args)...)) { }

template <typename memory_data_t, typename memory_controller_t>
memory::virtual_memory<memory_data_t, memory_controller_t>::~virtual_memory()
{
    memory_controller_t::deallocate(sizeof(memory_data_t), memory_pointer);
}