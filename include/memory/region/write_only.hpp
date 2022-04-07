#pragma once
#include <type_traits>

namespace memory::region::access {
	template <typename WronlyType, typename WronlyMemory>
	class write_only
	{
	public:
		using value_type	  = WronlyType;
		using pointer		  = WronlyType*;
		using reference		  = WronlyType&;
		using difference_type = std::int64_t;

		using memory_type	  =			 WronlyMemory;
		using size_type       = typename WronlyMemory::size_type;

	public:
		write_only(memory_type&, size_type, size_type);
	public:
		template <typename InputType>
		std::enable_if_t<std::is_same_v<std::decay_t<InputType>, value_type>, write_only&>
					 operator=  (InputType&& wrbuf) 
		{ 
			if(__M_wronly_counter != __M_wronly_range)
				*(__M_wronly_pointer + __M_wronly_counter) = wrbuf;
			
			return *this; 
		}
		
		write_only&  operator++()   ;
		write_only   operator++(int);

		write_only&  operator--()   ;
		write_only   operator--(int);

	private:
		pointer   __M_wronly_pointer;
		size_type __M_wronly_counter, __M_wronly_range;
	};
}

namespace memory::region {
namespace types			 {
	template <typename WronlyType, std::size_t RegionOffset, std::size_t RegionCount>
	struct write_only {};
}
	template <typename WronlyType, std::size_t RegionOffset, std::size_t RegionCount>
	inline constexpr types::write_only<WronlyType, RegionOffset, RegionCount> write_only;
}

template <typename MemoryObject, typename WronlyType, std::size_t RegionOffset, std::size_t RegionCount>
auto operator|(MemoryObject&& memobj, memory::region::types::write_only<WronlyType, RegionOffset, RegionCount>)
{
	return memory::region::access::write_only<WronlyType, std::decay_t<MemoryObject>>(memobj, RegionOffset, RegionCount);
}

template <typename WronlyType, typename WronlyMemory>
memory::region::access::write_only<WronlyType, WronlyMemory>::write_only(memory_type& memobj, size_type memoff, size_type memcount)
	: __M_wronly_pointer((pointer)(memobj.address() + memoff)),
	  __M_wronly_range  (memcount)							  ,
	  __M_wronly_counter(0)									  {   }

template <typename WronlyType, typename WronlyMemory>
memory::region::access::write_only<WronlyType, WronlyMemory>&
memory::region::access::write_only<WronlyType, WronlyMemory>::operator++()
{
	if (__M_wronly_counter + 1 <= __M_wronly_range)
		__M_wronly_counter++;

	return *this;
}

template <typename WronlyType, typename WronlyMemory>
memory::region::access::write_only<WronlyType, WronlyMemory>
memory::region::access::write_only<WronlyType, WronlyMemory>::operator++(int)
{
	if (__M_wronly_counter + 1 <= __M_wronly_range)
		__M_wronly_counter++;

	return *this;
}

template <typename WronlyType, typename WronlyMemory>
memory::region::access::write_only<WronlyType, WronlyMemory>&
memory::region::access::write_only<WronlyType, WronlyMemory>::operator--()
{
	if (__M_wronly_counter - 1 >= 0)
		__M_wronly_counter--;

	return *this;
}

template <typename WronlyType, typename WronlyMemory>
memory::region::access::write_only<WronlyType, WronlyMemory>
memory::region::access::write_only<WronlyType, WronlyMemory>::operator--(int)
{
	if (__M_wronly_counter - 1 >= 0)
		__M_wronly_counter--;

	return *this;
}