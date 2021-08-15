
namespace memory {
    template <typename T>
    concept bool pointer_accessible = requires(T& m) { m.get_pointer(); }

    template <typename T>
    concept bool allocatable   = requires(T& m) { m.allocate()  ; }

    template <typename T>
    concept bool deallocatable = requires(T& m) { m.deallocate(); }
}