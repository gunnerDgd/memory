#pragma once
#include <memory/io_map/io_map.hpp>

namespace memory {
	class io_map::viewer
	{
		viewer(io_map&, size_type, size_type);
	public:
		pointer_type address();
		size_type	 size	();

	private:
		io_map&		 __M_viewer_memobj ;
		pointer_type __M_viewer_address;

		size_type	 __M_viewer_begin ,
					 __M_viewer_end   ;
	};
}

template <memory::io_map::size_type ViewBegin, memory::io_map::size_type ViewEnd>
memory::io_map::viewer memory::io_map::get_view()
{
	if constexpr (ViewBegin > ViewEnd)
		return viewer(ViewEnd, ViewBegin);
	else
		return viewer(ViewBegin, ViewEnd);
}