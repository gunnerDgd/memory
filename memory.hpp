#include <type_traits>
#include <memory/vmem/vmem_controller.hpp>

namespace memory {

    template <typename memory_data_t, typename memory_controller_t>
    class virtual_memory;

    template <typename memory_data_t>
    class virtual_memory<memory_data_t, rmem_controller>
    {
    public:
        using pointer_type = typename std::conditional<std::is_array_v   <memory_data_t>,
                                                       std::remove_extent<memory_data_t>, 
                                                                          memory_data_t>::type*;
    public:
        virtual_memory (void* adjoin = nullptr) { (pointer_type)rmem_controller::allocate  (sizeof(memory_data_t), adjoin)        ; }
        ~virtual_memory()                       {               rmem_controller::deallocate(sizeof(memory_data_t), memory_pointer); }
    
        pointer_type get_pointer()              { return memory_pointer; }
    
    protected:
        pointer_type memory_pointer;
    };

    template <typename memory_data_t, typename memory_controller_t = vmem_controller>
    class virtual_memory
    {
    public:
        using pointer_type = typename std::conditional<std::is_array_v   <memory_data_t>,
                                                       std::remove_extent<memory_data_t>, 
                                                                          memory_data_t>::type*;
    public:
        virtual_memory (typename memory_controller_t::memory_prot_t prot = vmem_mode::read | vmem_mode::write, void* adjoin = nullptr);
        virtual_memory (virtual_memory<memory_data_t, rmem_controller>&, typename memory_controller_t::memory_prot_t);
        
        ~virtual_memory() { memory_controller_t::deallocate(sizeof(memory_data_t), memory_pointer); }
    
    public:
        pointer_type get_pointer() { return memory_pointer; }

    protected:
        pointer_type memory_pointer;
    };
}

template <typename memory_data_t, typename memory_controller_t>
memory::virtual_memory<memory_data_t, memory_controller_t>::virtual_memory (typename memory_controller_t::memory_prot_t prot, void* adjoin)
    : memory_pointer((pointer_type)memory_controller_t::allocate(prot, sizeof(memory_data_t), adjoin)) { }

template <typename memory_data_t, typename memory_controller_t>
memory::virtual_memory<memory_data_t, memory_controller_t>::virtual_memory (memory::virtual_memory<memory_data_t, rmem_controller>& reserved,
                                                                            typename memory_controller_t::memory_prot_t             prot)
    : memory_pointer(reserved.get_pointer()) { mprotect(memory_pointer, sizeof(memory_data_t), prot); }