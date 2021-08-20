#include <cstdint>

namespace memory {

    template <typename T, typename access_type>
    class vm_accessor_query
    {
    public:
        using ac_handle_t = typename access_type::access_handle_t;
        using ac_off_t    = typename access_type::access_off_t   ;
    public:
        static handle_t query_increase(handle_t h, ac_off_t o) { return (h += o); }
        static handle_t query_decrease(handle_t h, ac_off_t o) { return (h -= o); }
    
    public:
        static T        query_get_value(handle_t h)             { return *h; }
        static void     query_set_value(T v, handle_t h)        { *h    = v; }
    };
}