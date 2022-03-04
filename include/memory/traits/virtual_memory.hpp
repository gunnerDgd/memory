#pragma once
#include <Windows.h>
#include <memory/access/forward.hpp>

#include <type_traits>
#include <atomic>

namespace memory {
	class virtual_memory
	{
	public:
		class handle;
		using size_type = std::size_t;

	public:
		static handle create_memory(size_type);
		static bool   delete_memory(handle&);
	};

	class virtual_memory::handle
	{
		friend class access::virtual_memory;
		friend class		 virtual_memory;
	
		handle();
	public:
		using pointer_type    = std::uint8_t*;
		using size_type		  = std::size_t;
		using reference_count = std::atomic<std::uint32_t>;

	public:
		handle(handle&);
		handle(handle&&);

	private:
		pointer_type	__M_hnd_pointer ;
		size_type       __M_hnd_size    ;
		reference_count __M_hnd_refcount;
	};
}