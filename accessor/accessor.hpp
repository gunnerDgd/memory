#include <iostream>

namespace memory {

    template <typename T>
    class accessor_type
    {
    public:
        using            access_handle_t          = T*         ;
        using            access_size_t            = std::size_t;
        using            access_off_t             = std::size_t;
        static constexpr access_size_t block_size = sizeof(T)  ;
    };

    template <typename T, typename access_type, typename access_query>
    class accessor;

    template <typename T, typename access_type, typename access_query>
    class accessor
    {
    public:
        using accessor_handle = typename access_type::access_handle_t;
        using accessor_size   = typename access_type::access_size_t  ;
        using accessor_off    = typename access_type::access_off_t   ;

    public:
        accessor& operator++()    { ac_pointer = access_query::query_increase(ac_pointer, 1); return *this; }
        accessor& operator++(int) { ac_pointer = access_query::query_increase(ac_pointer, 1); return *this; }

        accessor& operator--()    { ac_pointer = access_query::query_increase(ac_pointer, 1); return *this; }
        accessor& operator--(int) { ac_pointer = access_query::query_increase(ac_pointer, 1); return *this; }

    public:
        T         operator* ()     { return access_query::query_get_value(ac_pointer); }
        void      operator= (T& v) {        access_query::query_set_value(ac_pointer); }

    protected:
        accessor_handle ac_handle, ac_pointer;
    }
}