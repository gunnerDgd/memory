#pragma once
#include <Windows.h>
#include <string>

namespace memory {
	class io_map
	{
	public:
		/*
		 * Neccessarily Defined Types
		 * 
		 * 1) pointer_type : Type of the pointer.
		 * 
		 */
		using			 native_handle_type				   = HANDLE;
		static constexpr native_handle_type invalid_handle = INVALID_HANDLE_VALUE;
		
		using			 pointer_type					   = std::uint8_t*;
		static constexpr pointer_type invalid_pointer	   = nullptr;

		using size_type	   = std::size_t ;

	public:
		io_map(std::string , size_type);
		io_map(std::string);

		io_map(std::wstring, size_type);
		io_map(std::wstring);
		
		io_map(io_map&) ;
		io_map(io_map&&);

	public:
		/*
		* Reguirements : Get Address and Size of Memory block.
		* pointer_type address_of() : returns actual memory address (pointer) of the io_map.
		*/
		pointer_type address(); 
		size_type    size	();

	private:
		native_handle_type __M_iomap_io_handle ,
						   __M_iomap_map_handle;
		
		size_type		   __M_iomap_size   ;
		pointer_type	   __M_iomap_pointer;
	};
}