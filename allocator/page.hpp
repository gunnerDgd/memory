#include <memory/virtual_memory/controller.hpp>

namespace memory    {
namespace allocator {

    class page
    {
    public:
        void* allocate  (uint64_t size, void* adjoin = nullptr) { return ::memory::vmem_controller::allocate  (size, adjoin); }
        void  deallocate(void* addr, uint64_t size)             {        ::memory::vmem_controller::deallocate(size, addr)  ; }
    };

}
}