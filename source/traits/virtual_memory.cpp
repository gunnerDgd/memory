#include <memory/virtual_memory/virtual_memory.hpp>

memory::virtual_memory::~virtual_memory()
{
	if (__M_hnd_pointer == invalid_pointer)
		return;

	::VirtualFree(__M_hnd_pointer, 0, MEM_RELEASE);
}

memory::virtual_memory::virtual_memory(const virtual_memory&  copy) : __M_hnd_pointer (copy.__M_hnd_pointer)		,
																	  __M_hnd_refcount(copy.__M_hnd_refcount.load()),
																	  __M_hnd_size	  (copy.__M_hnd_size)	        {  }

memory::virtual_memory::virtual_memory(const virtual_memory&& move) : __M_hnd_pointer (move.__M_hnd_pointer)		,
																	  __M_hnd_refcount(move.__M_hnd_refcount.load()),
																	  __M_hnd_size	  (move.__M_hnd_size)			{  }

typename memory::virtual_memory::pointer_type memory::virtual_memory::address()
{
	return __M_hnd_pointer;
}

typename memory::virtual_memory::size_type memory::virtual_memory::size()
{
	return __M_hnd_size;
}