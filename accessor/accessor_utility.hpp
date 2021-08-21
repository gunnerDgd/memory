#include <memory/accessor/accessor_forward.hpp>

namespace memory {

    template <typename Accessor, typename Fn>
    void for_each(Accessor& i, Fn&& f) requires std::is_invocable_v<Fn, Accessor&>                         { while(!i.is_end()) { f(i); i++; } }

    template <typename Accessor, typename Fn>
    void for_each(Accessor& i, Fn&& f) requires std::is_invocable_v<Fn, typename Accessor::accessor_block> { while(!i.is_end()) { f(*i); i++; } }

}