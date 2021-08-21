#include <memory/accessor/query/vm_access_query.hpp>
#include <memory/accessor/type/vm_access_type.hpp>
#include <memory/accessor/accessor.hpp>

namespace memory {

    template <typename T>
    using vmem_accessor = accessor<T, vm_access_type<T>, vm_access_query<T, vm_access_type<T>>>; 
}