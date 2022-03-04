#pragma once
#include <memory/traits/virtual_memory.hpp>
#include <memory/access.hpp>

namespace memory::access {
	class virtual_memory
	{
	public:
		template <typename AccessType>
		class read_only ;

		template <typename AccessType>
		class write_only;

	public:
		template <typename AccessType>
		static read_only<AccessType>  create_access(memory::access::read_only<AccessType> , memory::virtual_memory::handle&);
		template <typename AccessType>
		static write_only<AccessType> create_access(memory::access::write_only<AccessType>, memory::virtual_memory::handle&);
	};

	template <typename AccessType>
	class virtual_memory::read_only
	{
		friend class access::virtual_memory;
		using	  handle_type = memory::virtual_memory::handle;
		read_only(handle_type&);
	public:
		using value_type  = AccessType ;
		using pointer     = AccessType*;
		using reference   = AccessType&;
		using size_type   = std::size_t;

	public:
		const reference operator* ();
		void			operator++();

	private:
		handle_type& __M_rdonly_handle;
		size_type    __M_rdonly_rdptr = 0;
	};

	template <typename AccessType>
	class virtual_memory::write_only
	{
		friend class access::virtual_memory;
		using	   handle_type = memory::virtual_memory::handle;
		write_only(handle_type&);
	public:
		using value_type  = AccessType ;
		using pointer     = AccessType*;
		using reference   = AccessType&;
		using size_type   = std::size_t;

	public:
		template <typename InputType>
		void operator= (InputType&&);
		void operator++();

	private:
		handle_type& __M_wronly_handle;
		size_type    __M_wronly_wrptr = 0;
	};
}

template <typename AccessType>
memory::access::virtual_memory::read_only<AccessType>::read_only(handle_type& hnd) : __M_rdonly_handle(hnd) 
{
	(__M_rdonly_handle.__M_hnd_refcount)++;
}

template <typename AccessType>
typename memory::access::virtual_memory::read_only<AccessType>::reference
		 memory::access::virtual_memory::read_only<AccessType>::operator*()
{
	return *reinterpret_cast<pointer>(__M_rdonly_handle.__M_hnd_pointer + __M_rdonly_rdptr);
}

template <typename AccessType>
void memory::access::virtual_memory::read_only<AccessType>::operator++()
{
	if ((__M_rdonly_rdptr + sizeof(value_type)) >= __M_rdonly_handle.__M_hnd_size)
		return;

	__M_rdonly_rdptr += sizeof(value_type);
}

template <typename AccessType>
memory::access::virtual_memory::write_only<AccessType>::write_only(handle_type& hnd) : __M_wronly_handle(hnd) 
{
	(__M_wronly_handle.__M_hnd_refcount)++;
}

template <typename AccessType>
template <typename InputType>
void memory::access::virtual_memory::write_only<AccessType>::operator=(InputType&& input)
{
	*reinterpret_cast<pointer>(__M_wronly_handle.__M_hnd_pointer + __M_wronly_wrptr) = input;
}

template <typename AccessType>
void memory::access::virtual_memory::write_only<AccessType>::operator++()
{
	if ((__M_wronly_wrptr + sizeof(value_type)) >= __M_wronly_handle.__M_hnd_size)
		return;

	__M_wronly_wrptr += sizeof(value_type);
}

template <typename AccessType>
memory::access::virtual_memory::read_only<AccessType>
memory::access::virtual_memory::create_access(memory::access::read_only<AccessType>, memory::virtual_memory::handle& hnd)
{
	return read_only<AccessType>(hnd);
}

template <typename AccessType>
memory::access::virtual_memory::write_only<AccessType>
memory::access::virtual_memory::create_access(memory::access::write_only<AccessType>, memory::virtual_memory::handle& hnd)
{
	return write_only<AccessType>(hnd);
}