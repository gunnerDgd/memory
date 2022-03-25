#pragma once
#include <memory/virtual_memory/virtual_memory_access.hpp>

#include <type_traits>
#include <atomic>

namespace memory {
	class virtual_memory
	{
		friend class     virtual_memory;
		using		     pointer_type				  = std::uint8_t*;
		static constexpr pointer_type invalid_pointer = nullptr;	

		using		 size_type		 = std::size_t;
		using		 reference_count = std::atomic<std::uint32_t>;
	
	public:
		template <typename AccessMode>
		virtual_memory (AccessMode, size_type);
		~virtual_memory();

		virtual_memory(virtual_memory&);
		virtual_memory(virtual_memory&&);

	public:
		pointer_type address();
		size_type    size   ();
	private:
		pointer_type	__M_hnd_pointer ;
		size_type       __M_hnd_size    ;
		reference_count __M_hnd_refcount;
	};
}

template <typename AccessMode>
memory::virtual_memory::virtual_memory(AccessMode, size_type alloc_size) : __M_hnd_size	   (alloc_size),
																		   __M_hnd_refcount(0)		   ,
																		   __M_hnd_pointer (::VirtualAlloc(nullptr, __M_hnd_size, MEM_COMMIT, AccessMode::value)) {  }