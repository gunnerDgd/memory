#pragma once
#include <memory/traits/io_map.hpp>

namespace memory::access {
	class io_map
	{
	public:
		template <typename AccessType>
		class read_only ;
		template <typename AccessType>
		class write_only;
	};

	template <typename AccessType>
	class io_map::read_only
	{
		read_only (memory::io_map::handle& hnd) : __M_rdonly_handle(hnd) {  }
	public:

		using this_type   = read_only<AccessType>;
		using handle_type = memory::io_map::handle;

		using size_type   = typename handle_type::size_type;
		using value_type  = AccessType ;
		using pointer	  = AccessType*;
		using reference   = AccessType&;

		const reference operator*		();
		void			operator++	    ();

	private:
		handle_type& __M_rdonly_handle	 ;
		size_type    __M_rdonly_rdptr = 0;
	};

	template <typename AccessType>
	class io_map::write_only
	{
		write_only(memory::io_map::handle& hnd) : __M_wronly_handle(hnd) {  }
	public:

		using this_type   = write_only<AccessType>;
		using handle_type = memory::io_map::handle;

		using size_type   = typename handle_type::size_type;
		using value_type  = AccessType ;
		using pointer	  = AccessType*;
		using reference   = AccessType&;

		template <typename InputType>
		void operator= (InputType&&);
		void operator++();

	private:
		handle_type& __M_wronly_handle	 ;
		size_type    __M_wronly_wrptr = 0;
	};
}

template <typename AccessType>
const typename memory::access::io_map::read_only<AccessType>::reference 
			   memory::access::io_map::read_only<AccessType>::operator* ()
{
	return *reinterpret_cast<pointer>(__M_rdonly_handle.__M_iomap_pointer + __M_rdonly_rdptr);
}

template <typename AccessType>
void memory::access::io_map::read_only<AccessType>::operator++()
{
	if ((__M_rdonly_rdptr + sizeof(value_type)) < __M_rdonly_handle.__M_iomap_size)
		return;

	__M_rdonly_rdptr += sizeof(value_type);
}

template <typename AccessType>
template <typename InputType>
void memory::access::io_map::write_only<AccessType>::operator= (InputType&& input)
{
	*reinterpret_cast<pointer>(__M_wronly_handle.__M_iomap_pointer + __M_wronly_wrptr) = input;
}

template <typename AccessType>
void memory::access::io_map::write_only<AccessType>::operator++()
{
	if ((__M_wronly_wrptr + sizeof(value_type)) < __M_wronly_handle.__M_iomap_size)
		return;

	__M_wronly_wrptr += sizeof(value_type);
}