#pragma once
#include <memory/traits/virtual_memory.hpp>
#include <memory/access.hpp>

namespace memory::access {
	class virtual_memory
	{
	public:
		template <typename AccessType, typename Region = void>
		class read_only ;

		template <typename AccessType, typename Region = void>
		class write_only;

	public:
		template <typename AccessType, typename Region>
		static std::enable_if_t<std::is_same_v<Region, all_region>, read_only <AccessType, void>>
			create_access(memory::access::read_only<AccessType, Region> , memory::virtual_memory::handle& hnd) { return read_only <AccessType, void>(hnd); }
		template <typename AccessType, typename Region>
		static std::enable_if_t<std::is_same_v<Region, all_region>, write_only<AccessType>>
			create_access(memory::access::write_only<AccessType, Region>, memory::virtual_memory::handle& hnd) { return write_only<AccessType, void>(hnd); }

		template <typename AccessType, typename Region>
		static std::enable_if_t<!std::is_same_v<Region, all_region>, read_only <AccessType, Region>>
			create_access(memory::access::read_only<AccessType, Region> , memory::virtual_memory::handle& hnd) { return read_only <AccessType, Region>(hnd); }
		template <typename AccessType, typename Region>
		static std::enable_if_t<!std::is_same_v<Region, all_region>, write_only<AccessType, Region>>
			create_access(memory::access::write_only<AccessType, Region>, memory::virtual_memory::handle& hnd) { return write_only<AccessType, Region>(hnd); }
	};

	template <typename AccessType, typename Region>
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

		using region_type = Region;
		static constexpr size_type start = region_type::start;
		static constexpr size_type end   = region_type::end  ;

	public:
		const reference operator* ();
		void			operator++();

	private:
		handle_type& __M_rdonly_handle;
		size_type    __M_rdonly_rdptr = start;
	};

	template <typename AccessType>
	class virtual_memory::read_only<AccessType, void>
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

	template <typename AccessType, typename Region>
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

		using region_type = Region;
		static constexpr size_type start = region_type::start;
		static constexpr size_type end   = region_type::end  ;

	public:
		template <typename InputType>
		void operator= (InputType&&);
		void operator++();

	private:
		handle_type& __M_wronly_handle;
		size_type    __M_wronly_wrptr = start;
	};

	template <typename AccessType>
	class virtual_memory::write_only<AccessType, void>
	{
		friend class access::virtual_memory;
		using	   handle_type = memory::virtual_memory::handle;
		write_only(handle_type&);
	public:
		using value_type = AccessType;
		using pointer    = AccessType*;
		using reference  = AccessType&;
		using size_type  = std::size_t;

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
memory::access::virtual_memory::read_only<AccessType, void>::read_only(handle_type& hnd) : __M_rdonly_handle(hnd) 
{
	(__M_rdonly_handle.__M_hnd_refcount)++;
}

template <typename AccessType>
typename memory::access::virtual_memory::read_only<AccessType, void>::reference
		 memory::access::virtual_memory::read_only<AccessType, void>::operator*()
{
	return *reinterpret_cast<pointer>(__M_rdonly_handle.__M_hnd_pointer + __M_rdonly_rdptr);
}

template <typename AccessType>
void memory::access::virtual_memory::read_only<AccessType, void>::operator++()
{
	if ((__M_rdonly_rdptr + sizeof(value_type)) >= __M_rdonly_handle.__M_hnd_size)
		return;

	__M_rdonly_rdptr += sizeof(value_type);
}

template <typename AccessType>
memory::access::virtual_memory::write_only<AccessType, void>::write_only(handle_type& hnd) : __M_wronly_handle(hnd) 
{
	(__M_wronly_handle.__M_hnd_refcount)++;
}

template <typename AccessType>
template <typename InputType>
void memory::access::virtual_memory::write_only<AccessType, void>::operator=(InputType&& input)
{
	*reinterpret_cast<pointer>(__M_wronly_handle.__M_hnd_pointer + __M_wronly_wrptr) = input;
}



template <typename AccessType, typename Region>
memory::access::virtual_memory::read_only<AccessType, Region>::read_only(handle_type& hnd) : __M_rdonly_handle(hnd)
{
	(__M_rdonly_handle.__M_hnd_refcount)++;
}

template <typename AccessType, typename Region>
typename memory::access::virtual_memory::read_only<AccessType, Region>::reference
memory::access::virtual_memory::read_only<AccessType, Region>::operator*()
{
	return *reinterpret_cast<pointer>(__M_rdonly_handle.__M_hnd_pointer + __M_rdonly_rdptr);
}

template <typename AccessType, typename Region>
void memory::access::virtual_memory::read_only<AccessType, Region>::operator++()
{
	if ((__M_rdonly_rdptr + sizeof(value_type)) >= end)
		return;

	__M_rdonly_rdptr += sizeof(value_type);
}

template <typename AccessType, typename Region>
memory::access::virtual_memory::write_only<AccessType, Region>::write_only(handle_type& hnd) : __M_wronly_handle(hnd)
{
	(__M_wronly_handle.__M_hnd_refcount)++;
}

template <typename AccessType, typename Region>
template <typename InputType>
void memory::access::virtual_memory::write_only<AccessType, Region>::operator=(InputType&& input)
{
	*reinterpret_cast<pointer>(__M_wronly_handle.__M_hnd_pointer + __M_wronly_wrptr) = input;
}

template <typename AccessType, typename Region>
void memory::access::virtual_memory::write_only<AccessType, Region>::operator++()
{
	if ((__M_wronly_wrptr + sizeof(value_type)) >= end)
		return;

	__M_wronly_wrptr += sizeof(value_type);
}