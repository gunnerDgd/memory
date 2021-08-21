#pragma once

#include <memory/accessor/query/vm_access_query.hpp>
#include <memory/accessor/type/vm_access_type.hpp>
#include <memory/accessor/accessor.hpp>
#include <memory/memory_concepts.hpp>

namespace memory {

    template <typename T>
    using vmem_accessor = accessor<T, vm_access_type<T>, vm_access_query<T, vm_access_type<T>>>;

    template <typename... T>
    struct is_accessor                 { static constexpr bool value = false; };

    template <typename... T>
    struct is_accessor<accessor<T...>> { static constexpr bool value = true ; };

    template <pointer_accessible Memory>
    vmem_accessor<typename Memory::block_type> get_accessor(Memory& m) { return vmem_accessor<typename Memory::block_type>(m.get_pointer(), 
                                                                                                                           memory_size<Memory>::size / sizeof(typename Memory::block_type)); }
}