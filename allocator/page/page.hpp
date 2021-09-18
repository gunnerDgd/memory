#include <memory/virtual_memory/controller.hpp>
#include <memory/allocator/allocator.hpp>
#include <cstdint>

namespace memory    {
namespace allocator {

    template <>
    class memory_allocator<vmem_controller>
    {
    public:
        using this_type       = memory_allocator<vmem_controller>;
        using controller_type = vmem_controller;

        using size_type    = typename vmem_controller::memory_size_t;
        using locator_type = void*;

    public:
        static void* allocate  (size_type   size , locator_type adjoin = nullptr) { return controller_type::allocate  (size, adjoin); }
        static void  deallocate(locator_type addr, size_type    size)             {        controller_type::deallocate(size, addr)  ; }
    };

}
}