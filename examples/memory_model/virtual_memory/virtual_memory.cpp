#include <memory/memory_model.hpp>
#include <iostream>

int main()
{
	memory::model::virtual_memory vmem (256);
	memory::model::io_map		  iomap("test.txt");

	auto read  = vmem | memory::access::read_only <int>{};
	auto write = vmem | memory::access::write_only<int>{};

	write = 5;
	std::cout << *read << std::endl;
}