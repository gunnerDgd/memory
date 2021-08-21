#include <memory/memory>

int main()
{
    memory::memory<char[16]> test_memory(memory::vmem_mode::read | memory::vmem_mode::write);
    auto it                = memory::get_accessor(test_memory);

    memory::for_each(it, [&](memory::vmem_accessor<char>& i) { i = 'A'; }); it.start_point();
    memory::for_each(it, [&](char i) { std::cout << i;});

    std::cout << test_memory.get_pointer() << std::endl;
}