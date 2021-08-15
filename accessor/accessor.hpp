#include <iostream>

namespace memory {

    template <typename T>
    class accessor_type
    {
    public:
        using            memory_size_t            = std::size_t;
        static constexpr memory_size_t block_size = sizeof(T)  ;

    public:
        
    };
}