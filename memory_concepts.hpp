#pragma once
#include <memory/memory.hpp>

namespace memory {
    template <typename T>
    concept bool pointer_accessible = requires(T m) { m.get_pointer(); };

    template <typename... T>
    struct is_virtual_memory                       { static constexpr bool value = false; };

    template <typename...T>
    struct is_virtual_memory<::memory::virtual_memory<T...>> { static constexpr bool value = true ; };

    template <typename... T>
    struct controller_type {};

    template <typename T, typename C>
    struct controller_type<virtual_memory<T, C>> { using type = C; };

    template <typename T>
    using  controller_type_v = typename controller_type<T>::type;

    template <typename... T>
    struct memory_size {};

    template <typename T, typename C>
    struct memory_size<virtual_memory<T, C>> { static constexpr typename C::memory_size_t size = sizeof(T); };
}