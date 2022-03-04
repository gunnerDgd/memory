#include <memory/traits/virtual_memory.hpp>

memory::virtual_memory::handle memory::virtual_memory::create_memory(size_type cr_size)
{
	handle cr_handle;
		   cr_handle.__M_hnd_pointer  = (handle::pointer_type)::VirtualAlloc(nullptr, cr_size, MEM_COMMIT, PAGE_READWRITE);
		   cr_handle.__M_hnd_size     = cr_size;
		   cr_handle.__M_hnd_refcount = 0;

	return cr_handle;
}
bool memory::virtual_memory::delete_memory(handle& del_handle)
{
	if (del_handle.__M_hnd_refcount != 0)
		return false;

	::VirtualFree(del_handle.__M_hnd_pointer, del_handle.__M_hnd_size, MEM_DECOMMIT);
	::VirtualFree(del_handle.__M_hnd_pointer,						0, MEM_RELEASE) ;

	return true;
}

memory::virtual_memory::handle::handle() {  }

memory::virtual_memory::handle::handle(handle&  copy) : __M_hnd_pointer (copy.__M_hnd_pointer),
													    __M_hnd_refcount(copy.__M_hnd_refcount.load()),
														__M_hnd_size	(copy.__M_hnd_size)			  {  }

memory::virtual_memory::handle::handle(handle&& move) : __M_hnd_pointer (move.__M_hnd_pointer),
													    __M_hnd_refcount(move.__M_hnd_refcount.load()),
														__M_hnd_size	(move.__M_hnd_size)			  {  }