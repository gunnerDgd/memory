#include <memory/module/export/stdheap.h>
#include <memory/mman/os_specific/winheap/winheap.h>

#include <stdlib.h>

synapse_modules_component_interface
	synapse_memory_mman_winheap_export
		()
{
	synapse_modules_component_interface
		hnd_interface
			= {
				.construct
					= &synapse_memory_mman_stdheap_export_construct,
				.destruct
					= &synapse_memory_mman_stdheap_export_destruct,
				.duplicate
					= &synapse_memory_mman_stdheap_export_duplicate
			  };

	return
		hnd_interface;
}

void*
	synapse_memory_mman_winheap_export_construct
		(va_list pInitArgs)
{
	synapse_memory_mman_winheap*
		ptr_winheap_handle
			= malloc(sizeof(synapse_memory_mman_winheap));
		
	*ptr_winheap_handle
		= synapse_memory_mman_winheap_initialize
				(va_arg(pInitArgs, size_t), va_arg(pInitArgs, size_t));
	return
		ptr_winheap_handle;
}

void
	synapse_memory_mman_winheap_export_destruct
		(void* pVoidStdHeap)
{
	synapse_memory_mman_winheap_cleanup
		(*(synapse_memory_mman_winheap*)pVoidStdHeap);
	free
		(pVoidStdHeap);
}

void*
	synapse_memory_mman_winheap_export_duplicate
		(void* pVoidStdHeap)
{
	synapse_memory_mman_winheap*
		ptr_stdheap_handle
			= malloc(sizeof(synapse_memory_mman_winheap));
		
	*ptr_stdheap_handle
		= ((synapse_memory_mman_traits*)pVoidStdHeap)
				->hnd_mman;

	return
		ptr_stdheap_handle;
}