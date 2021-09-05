#pragma once
#include <tuple>
#include <type_traits>

/*
- Memory Class

1) Memory Object is "Accessible" Object.
    -> Accessible Object Must Define Following Aliases / Constexpr Values.
    -> block_type  : Type of the Object Block
    -> block_count : Count of the block_type objects.

2) 
*/

namespace memory {

    template <typename memory_data_t, typename memory_controller_t>
    class virtual_memory;

    template <typename memory_data_t, typename memory_controller_t>
    class virtual_memory
    {
    public:
        using                      size_type    = typename memory_controller_t::memory_size_t  ;
        using                      result_type  = typename memory_controller_t::memory_result_t;
        using                      prot_type    = typename memory_controller_t::memory_prot_t  ;

        using                      block_type   = std::conditional_t<std::is_array_v<memory_data_t>, std::remove_extent_t<memory_data_t>, memory_data_t>;
        using                      locator_type = std::add_pointer_t<block_type>;
        static constexpr size_type block_count  = sizeof(memory_data_t) / sizeof(block_type);
        
    public:
        template <typename... Args>
        virtual_memory (Args... vm_args);
        ~virtual_memory();
    
    public:
        locator_type get_locator() { return memory_pointer; }

    protected:
        locator_type memory_pointer;
    };
}
template <typename memory_data_t, typename memory_controller_t>
template <typename... Args>
memory::virtual_memory<memory_data_t, memory_controller_t>::virtual_memory (Args... vm_args)
    : memory_pointer((locator_type)memory_controller_t::allocate(sizeof(memory_data_t), std::forward<Args>(vm_args)...)) { }

template <typename memory_data_t, typename memory_controller_t>
memory::virtual_memory<memory_data_t, memory_controller_t>::~virtual_memory()
{
    memory_controller_t::deallocate(sizeof(memory_data_t), memory_pointer);
}