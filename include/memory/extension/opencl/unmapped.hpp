#pragma once
#include <accelerate/memory/unmapped/unmapped.hpp>

namespace memory::opencl {
	template <typename AccessType, typename AccessRange>
	class unmapped_pointer_trait
	{
	public:
		using value_type = AccessType;
		using pointer	 = AccessType;
		using reference  = AccessType;
		
		using range		  = AccessRange;
		using begin_point = AccessRange::begin;
		using end_point   = AccessRange::end;
		
		using handle_type     = accelerate::memory::unmapped;
		using size_type       = typename handle_type::size_type;
		using difference_type = typename handle_type::difference_type;

	public:
		unmapped_pointer_trait (handle_type&);
		~unmapped_pointer_trait();

	public:
		reference reference_from();
		void	  advance_to    (difference_type);
		void	  rewind_to     (differene_type);

	private:
		handle_type&    __M_trait_handle;
		difference_type __M_trait_accptr;
	};
}

template <typename AccessType, typename AccessRange>
memory::opencl::unmapped_pointer_trait<AccessType, AccessRange>::mapped_pointer_trait(handle_type& hnd)
	: __M_trait_handle(hnd)
{
}

template <typename AccessType, typename AccessRange>
typename memory::opencl::unmapped_pointer_trait<AccessType, AccessRange>::reference
		 memory::opencl::unmapped_pointer_trait<AccessType, AccessRange>::reference_from()
{
	
}

template <typename AccessType, typename AccessRange>
void	  advance_to(difference_type);

template <typename AccessType, typename AccessRange>
void	  rewind_to(differene_type);