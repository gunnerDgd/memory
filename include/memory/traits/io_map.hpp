#pragma once
#include <Windows.h>
#include <string>

#include <memory/access/forward.hpp>

namespace memory {
	class io_map
	{
	public:
		using native_handle_type = HANDLE;
		using size_type			 = std::size_t;

		class  handle;
		static handle create_memory(std::string , size_type);
		static handle create_memory(std::wstring, size_type);
		static bool   delete_memory(handle&);
	};

	class io_map::handle
	{
		friend class io_map;
		friend class memory::access::io_map;

		using native_handle_type = HANDLE;
		using size_type			 = std::size_t  ;
		using pointer_type       = std::uint8_t*;

		handle();
	public:
		handle(handle&) ;
		handle(handle&&);

	private:
		native_handle_type __M_iomap_io_handle ,
						   __M_iomap_map_handle;
		
		size_type		   __M_iomap_size   ;
		pointer_type	   __M_iomap_pointer;
	};
}