#include <memory/memory>

int main()
{
    memory::page test_page(memory::vmem_mode::read | memory::vmem_mode::write);
    auto it = memory::get_accessor(test_page);

    it   = 'A';
    ++it = 'B';

    it.start_point();
    std::cout << *it << std::endl; it++;
    std::cout << *it << std::endl;
}