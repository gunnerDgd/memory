#include <memory/memory_model.hpp>
#include <memory/access/io_map/read_only.hpp>	
#include <memory/access/io_map/write_only.hpp>
#include <iostream>

int main()
{
	memory::model::io_map io_map("test.txt", 256);
	const char*			  test_message = "Hello World";

	auto wronly = io_map | memory::write_only<char, 0, 256>();
	auto rdonly = io_map | memory::read_only <char, 0, 256>();

	for (int i = 0; i < strlen(test_message); i++, ++wronly)
		wronly = test_message[i];
		
	for (int i = 0; i < strlen(test_message); i++, ++rdonly)
		std::cout << *rdonly;
}