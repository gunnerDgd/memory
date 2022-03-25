#pragma once
#include <memory/pointer/declare.hpp>

namespace memory {
	template <typename PointerType, typename PointerRange, typename PointerTraits>
	class basic_access_pointer<pointer_category::address_based, PointerType, PointerRange, PointerTraits>
	{
	public:
		using value_type	  = PointerType  ;
		using reference		  = PointerType& ;
		
		using pointer		  = PointerType* ;
		using raw_pointer	  = std::uint8_t*;

		using size_type       = std::size_t;
		using difference_type = std::ptrdiff_t;

		using const_reference = const PointerType&;
		using const_pointer	  = const PointerType*;
		
		using traits_type	  =			 PointerTraits; 
		using handle_type	  = typename PointerTraits::handle_type;

		using access_range						= PointerRange;
		static constexpr size_type access_begin = access_range::begin;
		static constexpr size_type access_end   = access_range::end  ;

	public:
		template <typename MemoryObject>
		basic_access_pointer(MemoryObject&& memobj) : __M_pointer_base(memobj.address()),
													  __M_pointer_size(memobj.size	 ()) {  }

		~basic_access_pointer()	{  }

		reference operator* ()							{ return *reinterpret_cast<pointer>(__M_pointer_base + __M_pointer_accptr); }
		pointer	  operator->()						    { return  reinterpret_cast<pointer>(__M_pointer_base + __M_pointer_accptr); }

		auto&	   operator+ (difference_type add_diff) { __M_pointer_traits.advance_to(add_diff); return *this; }
		auto&	   operator- (difference_type sub_diff) { __M_pointer_traits.rewind_to (sub_diff); return *this; }

		auto&      operator++ ()					    { __M_pointer_base += sizeof(value_type); return *this; }
		auto       operator++ (int)						{ __M_pointer_base += sizeof(value_type); return *this; }


	private:
		raw_pointer		__M_pointer_base;
		size_type		__M_pointer_size;
		difference_type __M_pointer_accptr = access_begin;
	};
}