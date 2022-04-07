#include <memory/io_map/viewer.hpp>

memory::io_map::viewer::viewer(io_map& memobj, size_type begin, size_type end) 
	: __M_viewer_memobj(memobj),
	  __M_viewer_begin (begin) ,
	  __M_viewer_end   (end)   
{
	__M_viewer_address = (pointer_type)::MapViewOfFile(memobj.__M_iomap_map_handle,
													   FILE_MAP_ALL_ACCESS		  ,
													   begin >> 32			      ,
													   begin					  ,
													   end - begin);
}

typename memory::io_map::pointer_type 
		 memory::io_map::viewer::address() { return __M_viewer_address; }

typename memory::io_map::size_type
		 memory::io_map::viewer::size()	   { return __M_viewer_end - __M_viewer_begin; }