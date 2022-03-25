#include <memory/memory_model.hpp>
#include <memory/access/virtual_memory/read_only.hpp>
#include <memory/access/virtual_memory/write_only.hpp>

#include <iostream>

int main()
{
	memory::model::virtual_memory vmem (256);

	auto read  = vmem | memory::read_only <int, 0, 256>();
	auto write = vmem | memory::write_only<int, 0, 256>();

	write = 5;
	std::cout << *read << std::endl;
}