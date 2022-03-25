#pragma once
#include <memory/pointer/declare.hpp>

namespace memory {
	template <typename PointerType, typename PointerRange, typename PointerTraits>
	class basic_access_pointer<pointer_category::external_device, PointerType, PointerRange, PointerTraits>
	{
	public:
		using value_type	  = PointerTraits::value_type;
		using reference		  = PointerTraits::reference ;
		using pointer		  = PointerTraits::pointer   ;

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
		template <typename MemoryHandle>
		basic_access_pointer(MemoryHandle&& memhnd) : __M_pointer_handle(memhnd),
													  __M_pointer_traits(memhnd) {  }

		reference operator* ()						    { return __M_pointer_traits.reference_from(); }
		pointer   operator->()						    { return __M_pointer_traits.reference_from(); }

		auto&	   operator+ (difference_type add_diff) { __M_pointer_traits.advance_to(add_diff); return *this; }
		auto&	   operator- (difference_type sub_diff) { __M_pointer_traits.rewind_to (sub_diff); return *this; }

		auto&      operator++ ()						{ __M_pointer_traits.advance_to(1); return *this; }
		auto       operator++ (int)						{ __M_pointer_traits.advance_to(1); return *this; }

	private:
		handle_type&	__M_pointer_handle;
		traits_type		__M_pointer_traits;
	};
}