#include <type_traits>
#include <memory/vmem/vmem_controller.hpp>

namespace memory {

    template <typename memory_data_t, typename memory_controller_t>
    class virtual_memory;

    template <typename memory_data_t, typename memory_controller_t = vmem_controller>
    class virtual_memory
    {
    public:
        using pointer_type = typename std::conditional<std::is_array_v     <memory_data_t>,
                                                       std::remove_extent_t<memory_data_t>, 
                                                                            memory_data_t>::type*;안개성의
        
        using protect_type = typename memory_controller_t::memory_prot_t;
        using fd_type      = typename memory_controller_t::memory_fd_t  ;
    public:
        virtual_memory (protect_type prot = vmem_mode::read | vmem_mode::write, void* adjoin = nullptr, fd_type fd = memory_controller_t::memory_backed)
        virtual_memory ();
        ~virtual_memory();
    
    public:
        pointer_type allocate(protect_type p, void* a = nullptr, fd_type f = memory_controller_t::memory_backed);

        pointer_type get_pointer() { return memory_pointer; }

    protected:
        pointer_type                              memory_pointer      ;
        typename memory_controller_t::memory_fd_t memory_backup_object;
        
    };
}

template <typename memory_data_t, typename memory_controller_t>
memory::virtual_memory<memory_data_t, memory_controller_t>::virtual_memory (typename memory_controller_t::memory_prot_t prot  ,
                                                                            void*                                       adjoin,
                                                                            typename memory_controller_t::memory_fd_t   fd)
    : memory_pointer((pointer_type)memory_controller_t::allocate(prot, sizeof(memory_data_t), adjoin)) 
{

}

template <typename memory_data_t, typename memory_controller_t>
memory::virtual_memory<memory_data_t, memory_controller_t>::~virtual_memory() 
{ 
    memory_controller_t::deallocate(sizeof(memory_data_t), memory_pointer); 
}