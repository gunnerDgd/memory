#include <memory/virtual_memory/virtual_memory.hpp>
#include <memory/region/read_only.hpp>
#include <memory/region/write_only.hpp>

#include <iostream>

int main()
{
	memory::virtual_memory vmem(memory::access::virtual_memory::all, 256);

	auto read  = vmem | memory::region::read_only <int, 0, 1>;
	auto write = vmem | memory::region::write_only<int, 0, 1>;

	write = 15;
	std::cout << *read << std::endl;
}