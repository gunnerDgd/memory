#pragma once
#include <type_traits>

namespace memory::region::access {
	template <typename AccessType, typename AccessMemory>
	class access_pointer
	{
	public:
		using value_type	  = AccessType;
		using pointer		  = AccessType*;
		using reference		  = AccessType&;
		using difference_type = std::int64_t;

		using memory_type	  =			 AccessMemory;
		using size_type       = typename AccessMemory::size_type;

	public:
		access_pointer(memory_type&, size_type, size_type);
	public:
		template <typename InputType>
		std::enable_if_t<std::is_same_v<std::decay_t<InputType>, value_type>, access_pointer&>
					 operator=  (InputType&& wrbuf) 
		{ 
			if(__M_access_counter != __M_access_range)
				*(__M_access_pointer + __M_access_counter) = wrbuf;
			
			return *this; 
		}
		
		reference		 operator* ()   ;
		access_pointer&  operator++()   ;
		access_pointer   operator++(int);

		access_pointer&  operator--()   ;
		access_pointer   operator--(int);

	private:
		pointer   __M_access_pointer;
		size_type __M_access_counter, __M_access_range;
	};
}

namespace memory::region {
namespace types			 {
	template <typename AccessType, std::size_t RegionOffset, std::size_t RegionCount>
	struct access_range {};
}
	template <typename AccessType, std::size_t RegionOffset, std::size_t RegionCount>
	inline constexpr types::access_range<AccessType, RegionOffset, RegionCount> access_range;

	template <typename MemoryObject, typename AccessType, std::size_t RegionOffset, std::size_t RegionCount>
	auto operator|(MemoryObject&& memobj, types::access_range<AccessType, RegionOffset, RegionCount>)
	{
		return access::access_pointer<AccessType, std::decay_t<MemoryObject>>(memobj, RegionOffset, RegionCount);
	}
}

template <typename AccessType, typename AccessMemory>
memory::region::access::access_pointer<AccessType, AccessMemory>::access_pointer(memory_type& memobj, size_type memoff, size_type memcount)
	: __M_access_pointer((pointer)(memobj.address() + memoff)),
	  __M_access_range  (memcount)							  ,
	  __M_access_counter(0)									  {  }

template <typename AccessType, typename AccessMemory>
memory::region::access::access_pointer<AccessType, AccessMemory>&
memory::region::access::access_pointer<AccessType, AccessMemory>::operator++()
{
	if (__M_access_counter + 1 <= __M_access_range)
		__M_access_counter++;

	return *this;
}

template <typename AccessType, typename AccessMemory>
memory::region::access::access_pointer<AccessType, AccessMemory>
memory::region::access::access_pointer<AccessType, AccessMemory>::operator++(int)
{
	if (__M_access_counter + 1 <= __M_access_range)
		__M_access_counter++;

	return *this;
}

template <typename AccessType, typename AccessMemory>
memory::region::access::access_pointer<AccessType, AccessMemory>&
memory::region::access::access_pointer<AccessType, AccessMemory>::operator--()
{
	if (__M_access_counter - 1 >= 0)
		__M_access_counter--;

	return *this;
}

template <typename AccessType, typename AccessMemory>
memory::region::access::access_pointer<AccessType, AccessMemory>
memory::region::access::access_pointer<AccessType, AccessMemory>::operator--(int)
{
	if (__M_access_counter - 1 >= 0)
		__M_access_counter--;

	return *this;
}

template <typename AccessType, typename AccessMemory>
typename memory::region::access::access_pointer<AccessType, AccessMemory>::reference
		 memory::region::access::access_pointer<AccessType, AccessMemory>::operator*()
{
	return *(__M_access_pointer + __M_access_counter);
}