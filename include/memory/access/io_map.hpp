#pragma once
#include <memory/traits/io_map.hpp>

namespace memory::access {
	class io_map
	{
	public:
		template <typename AccessType, typename Region = void>
		class read_only ;
		template <typename AccessType, typename Region = void>
		class write_only;

		template <typename AccessType, typename Region>
		static std::enable_if_t<std::is_same_v<Region, all_region>, read_only <AccessType, void>>
			create_access(memory::access::read_only<AccessType, Region> , memory::io_map::handle& hnd) { return read_only <AccessType, void>(hnd); }
		template <typename AccessType, typename Region>
		static std::enable_if_t<std::is_same_v<Region, all_region>, write_only<AccessType, Region>>
			create_access(memory::access::write_only<AccessType, Region>, memory::io_map::handle& hnd) { return write_only<AccessType, void>(hnd); }

		template <typename AccessType, typename Region>
		static std::enable_if_t<!std::is_same_v<Region, all_region>, read_only <AccessType, Region>>
			create_access(memory::access::read_only<AccessType, Region> , memory::io_map::handle& hnd) { return read_only <AccessType, Region>(hnd); }
		template <typename AccessType, typename Region>
		static std::enable_if_t<!std::is_same_v<Region, all_region>, write_only<AccessType, Region>>
			create_access(memory::access::write_only<AccessType, Region>, memory::io_map::handle& hnd) { return write_only<AccessType, Region>(hnd); }
	};

	template <typename AccessType, typename Region>
	class io_map::read_only
	{
		friend class memory::access::io_map;

		read_only (memory::io_map::handle& hnd) : __M_rdonly_handle(hnd) {  }
	public:
		~read_only()													 {  }

		using this_type   = read_only<AccessType>;
		using handle_type = memory::io_map::handle;

		using size_type   = typename handle_type::size_type;
		using value_type  = AccessType ;
		using pointer	  = AccessType*;
		using reference   = AccessType&;

		using region_type = Region;
		static constexpr size_type start = region_type::start;
		static constexpr size_type end   = region_type::end  ;

		const reference operator*		();
		void			operator++	    ();

	private:
		handle_type& __M_rdonly_handle		 ;
		size_type    __M_rdonly_rdptr = start;
	};

	template <typename AccessType, typename Region>
	class io_map::write_only
	{
		friend class memory::access::io_map;

		write_only (memory::io_map::handle& hnd) : __M_wronly_handle(hnd) {  }
	public:
		~write_only()													  {  }

		using this_type   = write_only<AccessType>;
		using handle_type = memory::io_map::handle;

		using size_type   = typename handle_type::size_type;
		using value_type  = AccessType ;
		using pointer	  = AccessType*;
		using reference   = AccessType&;

		using region_type = Region;
		static constexpr size_type start = region_type::start;
		static constexpr size_type end   = region_type::end  ;

		template <typename InputType>
		void operator= (InputType&&);
		void operator++();

	private:
		handle_type& __M_wronly_handle		 ;
		size_type    __M_wronly_wrptr = start;
	};

	template <typename AccessType>
	class io_map::read_only<AccessType, void>
	{
		friend class memory::access::io_map;
		read_only(memory::io_map::handle& hnd) : __M_rdonly_handle(hnd) {  }
	public:

		using this_type   = read_only<AccessType>;
		using handle_type = memory::io_map::handle;

		using size_type   = typename handle_type::size_type;
		using value_type  = AccessType;
		using pointer     = AccessType*;
		using reference   = AccessType&;

		const reference operator*		();
		void			operator++	    ();

	private:
		handle_type& __M_rdonly_handle;
		size_type    __M_rdonly_rdptr = 0;
	};

	template <typename AccessType>
	class io_map::write_only<AccessType, void>
	{
		friend class memory::access::io_map;
		write_only(memory::io_map::handle& hnd) : __M_wronly_handle(hnd) {  }
	public:

		using this_type   = write_only<AccessType>;
		using handle_type = memory::io_map::handle;

		using size_type   = typename handle_type::size_type;
		using value_type  = AccessType;
		using pointer     = AccessType*;
		using reference   = AccessType&;

		template <typename InputType>
		void operator= (InputType&&);
		void operator++();

	private:
		handle_type& __M_wronly_handle;
		size_type    __M_wronly_wrptr = 0;
	};
}

template <typename AccessType>
const typename memory::access::io_map::read_only<AccessType, void>::reference 
			   memory::access::io_map::read_only<AccessType, void>::operator* ()
{
	return *reinterpret_cast<pointer>(__M_rdonly_handle.__M_iomap_pointer + __M_rdonly_rdptr);
}

template <typename AccessType>
void memory::access::io_map::read_only<AccessType, void>::operator++()
{
	if ((__M_rdonly_rdptr + sizeof(value_type)) >= __M_rdonly_handle.__M_iomap_size)
		return;

	__M_rdonly_rdptr += sizeof(value_type);
}

template <typename AccessType>
template <typename InputType>
void memory::access::io_map::write_only<AccessType, void>::operator= (InputType&& input)
{
	*reinterpret_cast<pointer>(__M_wronly_handle.__M_iomap_pointer + __M_wronly_wrptr) = input;
}

template <typename AccessType>
void memory::access::io_map::write_only<AccessType, void>::operator++()
{
	if ((__M_wronly_wrptr + sizeof(value_type)) >= __M_wronly_handle.__M_iomap_size)
		return;

	__M_wronly_wrptr += sizeof(value_type);
}


template <typename AccessType, typename Region>
const typename memory::access::io_map::read_only<AccessType, Region>::reference 
			   memory::access::io_map::read_only<AccessType, Region>::operator* ()
{
	return *reinterpret_cast<pointer>(__M_rdonly_handle.__M_iomap_pointer + __M_rdonly_rdptr);
}

template <typename AccessType, typename Region>
void memory::access::io_map::read_only<AccessType, Region>::operator++()
{
	if ((__M_rdonly_rdptr + sizeof(value_type)) >= end)
		return;

	__M_rdonly_rdptr += sizeof(value_type);
}

template <typename AccessType, typename Region>
template <typename InputType>
void memory::access::io_map::write_only<AccessType, Region>::operator= (InputType&& input)
{
	*reinterpret_cast<pointer>(__M_wronly_handle.__M_iomap_pointer + __M_wronly_wrptr) = input;
}

template <typename AccessType, typename Region>
void memory::access::io_map::write_only<AccessType, Region>::operator++()
{
	if ((__M_wronly_wrptr + sizeof(value_type)) >= end)
		return;

	__M_wronly_wrptr += sizeof(value_type);
}