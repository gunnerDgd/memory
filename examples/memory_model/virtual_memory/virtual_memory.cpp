#include <memory/memory_model.hpp>
#include <iostream>

int main()
{
	memory::model::virtual_memory vmem (256);

	auto read  = vmem | (memory::access::read_only <int>{} | memory::access::region<0, 100>{});
	auto write = vmem | (memory::access::write_only<int>{} | memory::access::region<0, 100>{});

	write = 5;
	std::cout << *read << std::endl;
}