#pragma once
#include <memory/access.hpp>

namespace memory {
	template <typename MemoryTraits, typename MemoryAccess>
	class basic_memory_model
	{
	public:
		using handle		= typename MemoryTraits::handle;
		using size_type		= typename MemoryTraits::size_type;
		using traits		= MemoryTraits;
		using access_traits = MemoryAccess;
		using this_type		= basic_memory_model<MemoryTraits, MemoryAccess>;

	public:
		template <typename... InitArgs>
		basic_memory_model (InitArgs&&...);
		
		basic_memory_model  (this_type&) = delete;
		this_type& operator=(this_type&) = delete;
		
		basic_memory_model  (this_type&&);
		this_type& operator=(this_type&&);

		~basic_memory_model ();

	public:
		template <typename AccessType, typename Region>
		auto operator|(access::read_only <AccessType, Region>);
		template <typename AccessType, typename Region>
		auto operator|(access::write_only<AccessType, Region>);

	private:
		handle __M_mmodel_handle;
	};
}

template <typename MemoryTraits, typename MemoryAccess>
template <typename AccessType, typename Region>
auto memory::basic_memory_model<MemoryTraits, MemoryAccess>::operator|(access::read_only<AccessType, Region>)
{
	return access_traits::create_access(access::read_only<AccessType, Region>{}, __M_mmodel_handle);
}

template <typename MemoryTraits, typename MemoryAccess>
template <typename AccessType, typename Region>
auto memory::basic_memory_model<MemoryTraits, MemoryAccess>::operator|(access::write_only<AccessType, Region>)
{
	return access_traits::create_access(access::write_only<AccessType, Region>{}, __M_mmodel_handle);
}

template <typename MemoryTraits, typename MemoryAccess>
template <typename... InitArgs>
memory::basic_memory_model<MemoryTraits, MemoryAccess>::basic_memory_model(InitArgs&&... init_args) 
	: __M_mmodel_handle(traits::create_memory(std::forward<InitArgs>(init_args)...)) {  }

template <typename MemoryTraits, typename MemoryAccess>
memory::basic_memory_model<MemoryTraits, MemoryAccess>::basic_memory_model(this_type&& move)
	: __M_mmodel_handle(std::move(move.__M_mmodel_handle))    {  }

template <typename MemoryTraits, typename MemoryAccess>
memory::basic_memory_model<MemoryTraits, MemoryAccess>::~basic_memory_model()
{
	traits::delete_memory(__M_mmodel_handle);
}

template <typename MemoryTraits, typename MemoryAccess>
typename memory::basic_memory_model<MemoryTraits, MemoryAccess>::this_type& 
		 memory::basic_memory_model<MemoryTraits, MemoryAccess>::operator=(this_type&& move)

{
	__M_mmodel_handle = std::move(move.__M_mmodel_handle);
	return *this;
}