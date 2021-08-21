#include <iostream>

namespace memory {

    template <typename T, typename access_type, typename access_query>
    class accessor;

/*

Accessor Class

1) Template 
- T            : Type to Access.
- access_type  : Type for Accessing Values.
- access_query : Query Function for Accessing Values.

2) Restraints

- accessor_handle (alias for access_type::access_handle_t)
    --> 


*/

    template <typename T, typename access_type, typename access_query>
    class accessor
    {
    public:
        using accessor_t      = accessor<T, access_type, access_query>;
        using accessor_handle = typename access_type::access_handle_t ;
        using accessor_size   = typename access_type::access_size_t   ;
        using accessor_off    = typename access_type::access_off_t    ;

    public:
        accessor(accessor_handle h, accessor_size s)
            : ac_handle(h), ac_size(s) { }

    public:
        accessor_t& operator++()   ;
        accessor_t& operator++(int);

        accessor_t& operator--()   ;
        accessor_t& operator--(int);

    public:
        T         operator* ()     { return access_query::query_get_value   (ac_handle); }
        void      operator= (T& v) {        access_query::query_set_value(v, ac_handle); }

    protected:
        accessor_handle ac_handle;
        accessor_size   ac_size, ac_pointer = 0;
    };
}

template <typename T, typename access_type, typename access_query>
typename memory::accessor<T, access_type, access_query>::accessor_t& memory::accessor<T, access_type, access_query>::operator++()
{ 
    if(ac_pointer >= ac_size)
        return *this;
    else 
    {
        ac_pointer++; 
        access_query::query_increase(ac_handle, 1); 
    }
    
    return *this; 
}

template <typename T, typename access_type, typename access_query>
typename memory::accessor<T, access_type, access_query>::accessor_t& memory::accessor<T, access_type, access_query>::operator++(int)
{
    if(ac_pointer >= ac_size)
        return *this;
    else
    {
        ac_pointer++; 
        access_query::query_increase(ac_handle, 1);
    }
    
    return *this;
}

template <typename T, typename access_type, typename access_query>
typename memory::accessor<T, access_type, access_query>::accessor_t& memory::accessor<T, access_type, access_query>::operator--()
{ 
    if(ac_pointer == 0)
        return *this;
    else
    {
        ac_pointer--;
        access_query::query_increase(ac_handle, 1); 
    }

    return *this; 
}

template <typename T, typename access_type, typename access_query>
typename memory::accessor<T, access_type, access_query>::accessor_t& memory::accessor<T, access_type, access_query>::operator--(int)
{
    if(ac_pointer == 0)
        return *this;
    else
    {
        ac_pointer--; 
        access_query::query_increase(ac_handle, 1); 
    }
    
    return *this; 
}