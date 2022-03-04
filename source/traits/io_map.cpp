#include <memory/traits/io_map.hpp>

memory::io_map::handle memory::io_map::create_memory(std::string name, size_type view_range)
{
	handle cr_handle;
		   cr_handle.__M_iomap_io_handle = ::CreateFileA(name.c_str(), GENERIC_ALL, 0, 0, OPEN_EXISTING, 0, 0);

	if (cr_handle.__M_iomap_io_handle == INVALID_HANDLE_VALUE)
		cr_handle.__M_iomap_io_handle = ::CreateFileA(name.c_str(), GENERIC_ALL, 0, 0, CREATE_ALWAYS, 0, 0);

	cr_handle.__M_iomap_map_handle =					   ::CreateFileMappingA(cr_handle.__M_iomap_io_handle , 0, PAGE_READWRITE, view_range >> 32, view_range, NULL);
	cr_handle.__M_iomap_pointer    = (handle::pointer_type)::MapViewOfFile	   (cr_handle.__M_iomap_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	cr_handle.__M_iomap_size	   = view_range;

	return cr_handle;
}

memory::io_map::handle memory::io_map::create_memory(std::wstring name, size_type view_range)
{
	handle cr_handle;
		   cr_handle.__M_iomap_io_handle = ::CreateFileW(name.c_str(), GENERIC_ALL, 0, 0, OPEN_EXISTING, 0, 0);

	if (cr_handle.__M_iomap_io_handle == INVALID_HANDLE_VALUE)
		cr_handle.__M_iomap_io_handle = ::CreateFileW(name.c_str(), GENERIC_ALL, 0, 0, CREATE_ALWAYS, 0, 0);

	cr_handle.__M_iomap_map_handle =					   ::CreateFileMappingW(cr_handle.__M_iomap_io_handle , 0, PAGE_READWRITE, view_range >> 32, view_range, NULL);
	cr_handle.__M_iomap_pointer    = (handle::pointer_type)::MapViewOfFile	   (cr_handle.__M_iomap_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	cr_handle.__M_iomap_size	   = view_range;

	return cr_handle;
}

bool memory::io_map::delete_memory(handle& del_handle)
{
	::UnmapViewOfFile(del_handle.__M_iomap_pointer)   ;
	::CloseHandle	 (del_handle.__M_iomap_map_handle);
	::CloseHandle	 (del_handle.__M_iomap_io_handle) ;
}

memory::io_map::handle::handle(handle& copy) : __M_iomap_io_handle (copy.__M_iomap_io_handle) ,
											   __M_iomap_map_handle(copy.__M_iomap_map_handle),
											   __M_iomap_pointer   (copy.__M_iomap_pointer)	  ,
											   __M_iomap_size	   (copy.__M_iomap_size)      {  }

memory::io_map::handle::handle(handle&& move) : __M_iomap_io_handle (move.__M_iomap_io_handle) ,
											    __M_iomap_map_handle(move.__M_iomap_map_handle),
											    __M_iomap_pointer   (move.__M_iomap_pointer)   ,
											    __M_iomap_size	    (move.__M_iomap_size)      {  }