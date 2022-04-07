#pragma once
#include <type_traits>

namespace memory::region::access {
	template <typename RdonlyType, typename RdonlyMemory>
	class read_only
	{
	public:
		using value_type	  = RdonlyType ;
		using pointer		  = RdonlyType*;
		using reference		  = RdonlyType&;
		using difference_type = std::int64_t;

		using memory_type	  =			 RdonlyMemory;
		using size_type       = typename RdonlyMemory::size_type;

	public:
		read_only(memory_type&, size_type, size_type);
	public:
		value_type  operator* ()   ;
		
		read_only&  operator++()   ;
		read_only   operator++(int);

		read_only&  operator--()   ;
		read_only   operator--(int);

	private:
		pointer   __M_rdonly_pointer;
		size_type __M_rdonly_counter, __M_rdonly_range;
	};
}

namespace memory::region {
namespace types			 {
	template <typename RdonlyType, std::size_t RegionOffset, std::size_t RegionCount>
	struct read_only {};
}
	template <typename RdonlyType, std::size_t RegionOffset, std::size_t RegionCount>
	inline constexpr types::read_only<RdonlyType, RegionOffset, RegionCount> read_only;
}
template <typename MemoryObject, typename RdonlyType, std::size_t RegionOffset, std::size_t RegionCount>
auto operator|(MemoryObject&& memobj, memory::region::types::read_only<RdonlyType, RegionOffset, RegionCount>)
{
	return memory::region::access::read_only<RdonlyType, std::decay_t<MemoryObject>>(memobj, RegionOffset, RegionCount);
}

template <typename RdonlyType, typename RdonlyMemory>
memory::region::access::read_only<RdonlyType, RdonlyMemory>::read_only(memory_type& memobj, size_type memoff, size_type memcount)
	: __M_rdonly_pointer((pointer)(memobj.address() + memoff)),
	  __M_rdonly_range  (memcount)							  ,
	  __M_rdonly_counter(0)									  {  }

template <typename RdonlyType, typename RdonlyMemory>
typename memory::region::access::read_only<RdonlyType, RdonlyMemory>::value_type  
		 memory::region::access::read_only<RdonlyType, RdonlyMemory>::operator* ()
{
	return *(__M_rdonly_pointer + __M_rdonly_counter);
}

template <typename RdonlyType, typename RdonlyMemory>
memory::region::access::read_only<RdonlyType, RdonlyMemory>& 
memory::region::access::read_only<RdonlyType, RdonlyMemory>::operator++()
{
	if (__M_rdonly_counter + 1 <= __M_rdonly_range)
		__M_rdonly_counter++;

	return *this;
}

template <typename RdonlyType, typename RdonlyMemory>
memory::region::access::read_only<RdonlyType, RdonlyMemory>   
memory::region::access::read_only<RdonlyType, RdonlyMemory>::operator++(int)
{
	if (__M_rdonly_counter + 1 <= __M_rdonly_range)
		__M_rdonly_counter++;

	return *this;
}

template <typename RdonlyType, typename RdonlyMemory>
memory::region::access::read_only<RdonlyType, RdonlyMemory>&
memory::region::access::read_only<RdonlyType, RdonlyMemory>::operator--()
{
	if (__M_rdonly_counter - 1 >= 0)
		__M_rdonly_counter--;

	return *this;
}

template <typename RdonlyType, typename RdonlyMemory>
memory::region::access::read_only<RdonlyType, RdonlyMemory>
memory::region::access::read_only<RdonlyType, RdonlyMemory>::operator--(int)
{
	if (__M_rdonly_counter - 1 >= 0)
		__M_rdonly_counter--;

	return *this;
}