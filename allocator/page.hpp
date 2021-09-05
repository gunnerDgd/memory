#include <memory/virtual_memory/controller.hpp>

namespace memory    {
namespace allocator {

    class page
    {
    public:
        using size_type    = uint64_t;
        using locator_type = void*

    public:
        static void* allocate  (size_type   size , locator_type adjoin = nullptr) { return ::memory::vmem_controller::allocate  (size, adjoin); }
        static void  deallocate(locator_type addr, size_type    size)             {        ::memory::vmem_controller::deallocate(size, addr)  ; }
    };

}
}