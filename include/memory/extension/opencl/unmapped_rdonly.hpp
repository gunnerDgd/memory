#pragma once
#include <memory/traits/opencl/unmapped.hpp>

namespace memory::opencl {
	class unmapped_memory::rdonly
	{
	public:
		using  native_handle_type = accelerate::memory::unmapped::read_only;
		using  handle			  = native_handle_type;

		static handle create_memory(cl_executor_type&, size_type);
		static void   delete_memory(handle&);

	public:
		template <typename ReadType, typename ReadRegion>     class read_only;
		template <typename WriteType, typename WriteRegion>   class write_only;
		template <typename AccessType, typename AccessRegion> class accessor;
	};

	template <typename ReadType, typename ReadRegion>
	class unmapped_memory::rdonly::read_only
	{

	};
}

typename memory::opencl::unmapped_memory::rdonly::handle
memory::opencl::unmapped_memory::rdonly::create_memory(cl_executor_type& exec, size_type size)
{
	return handle(exec, size);
}

void memory::opencl::unmapped_memory::rdonly::delete_memory(handle&) { }

