#include <iostream>

namespace memory {

    template <typename T>
    class accessor_type
    {
    public:
        using            memory_size_t            = std::size_t;
        using            memory_off_t             = std::size_t;
        static constexpr memory_size_t block_size = sizeof(T)  ;
    };

    template <typename T, typename type_t = accessor_type<T>>
    class reader
    {
    public:
        reader(T*& pointer, typename type_t::memory_size_t size)
            : accessor_memory     (pointer)         ,
              accessor_memory_size(size)            ,
              accessor_block_count(size / sizeof(T)) { }

        const T& operator[] (typename type_t::memory_off_t offset) { return accessor_memory[]; }

    public:
        T*                             accessor_memory     ;
        typename type_t::memory_size_t accessor_memory_size;
        typename type_t::memory_size_t accessor_block_count;
    };
}