#include <iostream>
#include <cstdint>

namespace memory {
    template <typename T>
    class vm_access_type
    {
    public:
        using            access_handle_t          = T*         ;
        using            access_size_t            = std::size_t;
        using            access_off_t             = std::size_t;
        static constexpr access_size_t block_size = sizeof(T)  ;
    };
}