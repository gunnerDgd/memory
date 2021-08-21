#include <memory/memory>

template <typename T>
concept bool is_accessible = requires(T t) { t.get_accessor(); };

template <is_accessible T>
void test(T& t)
{
    std::cout << *(t.get_accessor()) << std::endl;
}

int main()
{
    memory::page test_page(memory::vmem_mode::read | memory::vmem_mode::write);
    auto ip = test_page.get_pointer();
    *ip = 'A';

    test(test_page);
}