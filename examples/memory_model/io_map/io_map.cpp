#include <memory/memory_model.hpp>
#include <iostream>

int main()
{
	memory::model::io_map io_map("test.txt", 256);
	const char*			  test_message = "Hello World";

	auto wronly = io_map | (memory::access::write_only<char>{} | memory::access::region<0, 10>{});
	auto rdonly = io_map | (memory::access::read_only <char>{} | memory::access::region<0, 10>{});

	for (int i = 0; i < strlen(test_message); i++, ++wronly)
		wronly = test_message[i];
		
	for (int i = 0; i < strlen(test_message); i++, ++rdonly)
		std::cout << *rdonly;
}