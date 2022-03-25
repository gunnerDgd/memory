#include <memory/io_map/io_map.hpp>

memory::io_map::io_map(std::string name, size_type size) : __M_iomap_size(size) 
{
	    __M_iomap_io_handle	= ::CreateFileA(name.c_str(), GENERIC_ALL, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (__M_iomap_io_handle == invalid_handle)
		return;

	__M_iomap_map_handle =				  ::CreateFileMappingA(__M_iomap_io_handle, NULL, PAGE_READWRITE, size >> 32, size, NULL);
	__M_iomap_pointer	 = (std::uint8_t*)::MapViewOfFile	  (__M_iomap_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, size);
}

memory::io_map::io_map(std::wstring name, size_type size) : __M_iomap_size(size) 
{
	    __M_iomap_io_handle	= ::CreateFileW(name.c_str(), GENERIC_ALL, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (__M_iomap_io_handle == invalid_handle)
		return;

	__M_iomap_map_handle =				  ::CreateFileMappingW(__M_iomap_io_handle, NULL, PAGE_READWRITE, size >> 32, size, NULL);
	__M_iomap_pointer	 = (std::uint8_t*)::MapViewOfFile	  (__M_iomap_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, size);
}

memory::io_map::io_map(std::string name) 
{
	    __M_iomap_io_handle	= ::CreateFileA(name.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (__M_iomap_io_handle == invalid_handle)
		return;

	std::uint32_t iomap_size_high,
				  iomap_size_low = ::GetFileSize(__M_iomap_io_handle, (LPDWORD)&iomap_size_high);

	__M_iomap_size		 = (iomap_size_high << 32) | (iomap_size_low);
	__M_iomap_map_handle =				 ::CreateFileMappingA(__M_iomap_io_handle, NULL, PAGE_READWRITE, 0, 0, NULL);
	__M_iomap_pointer	 = (pointer_type)::MapViewOfFile	 (__M_iomap_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
}

memory::io_map::io_map(std::wstring name)
{
		__M_iomap_io_handle	= ::CreateFileW(name.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (__M_iomap_io_handle == invalid_handle)
		return;

	std::uint32_t iomap_size_high,
				  iomap_size_low = ::GetFileSize(__M_iomap_io_handle, (LPDWORD)&iomap_size_high);

	__M_iomap_size		 = (iomap_size_high << 32) | (iomap_size_low);
	__M_iomap_map_handle =			     ::CreateFileMappingW(__M_iomap_io_handle, NULL, PAGE_EXECUTE_READWRITE, 0, 0, NULL);
	__M_iomap_pointer    = (pointer_type)::MapViewOfFile     (__M_iomap_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
}

memory::io_map::io_map(io_map& copy) : __M_iomap_io_handle (copy.__M_iomap_io_handle) ,
									   __M_iomap_map_handle(copy.__M_iomap_map_handle),
									   __M_iomap_pointer   (copy.__M_iomap_pointer)	  ,
									   __M_iomap_size	   (copy.__M_iomap_size)      {  }

memory::io_map::io_map(io_map&& move) : __M_iomap_io_handle (move.__M_iomap_io_handle) ,
									    __M_iomap_map_handle(move.__M_iomap_map_handle),
									    __M_iomap_pointer   (move.__M_iomap_pointer)   ,
									    __M_iomap_size	    (move.__M_iomap_size)      
{
	move.__M_iomap_io_handle  = invalid_handle;
	move.__M_iomap_map_handle = invalid_handle;
	
	move.__M_iomap_pointer	  = nullptr;
	move.__M_iomap_size		  = 0;
}

memory::io_map::pointer_type memory::io_map::address() { return __M_iomap_pointer; }
memory::io_map::size_type    memory::io_map::size   () { return __M_iomap_size   ; }