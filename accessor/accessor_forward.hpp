#include <memory/accessor/query/vm_access_query.hpp>
#include <memory/accessor/type/vm_access_type.hpp>
#include <memory/accessor/accessor.hpp>
#include <memory/memory_concepts.hpp>

namespace memory {

    template <typename T>
    using vmem_accessor = accessor<T, vm_access_type<T>, vm_access_query<T, vm_access_type<T>>>;

    template <pointer_accessible Memory>
    vmem_accessor<typename Memory::vm_block_t> get_accessor(Memory& m) { return vmem_accessor<typename Memory::vm_block_t>(m.get_pointer(), memory_size<Memory>::size); }
}