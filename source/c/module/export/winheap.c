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
	synapse_memory_mman_traits*
		ptr_stdheap_traits
		= malloc(sizeof(synapse_memory_mman_traits));
		
	ptr_stdheap_traits->hnd_mman
		= synapse_memory_mman_winheap_initialize
				(va_arg(pInitArgs, size_t), va_arg(pInitArgs, size_t));
	ptr_stdheap_traits->allocate
		= &synapse_memory_mman_winheap_allocate;
	ptr_stdheap_traits->deallocate
		= &synapse_memory_mman_winheap_deallocate;
	ptr_stdheap_traits->alloc_unit
		= NULL;

	va_end(pInitArgs);
	return
		ptr_stdheap_traits;
}

void
	synapse_memory_mman_winheap_export_destruct
		(void* pVoidStdHeap)
{
	synapse_memory_mman_winheap_cleanup
		(((synapse_memory_mman_traits*)pVoidStdHeap)
			->hnd_mman);
	free
		(pVoidStdHeap);
}

void*
	synapse_memory_mman_winheap_export_duplicate
		(void* pVoidStdHeap)
{
	synapse_memory_mman_traits*
		ptr_stdheap_traits
			= malloc(sizeof(synapse_memory_mman_traits));
		
	ptr_stdheap_traits->hnd_mman
		= ((synapse_memory_mman_traits*)pVoidStdHeap)
				->hnd_mman;
	ptr_stdheap_traits->allocate
		= &synapse_memory_mman_winheap_allocate;
	ptr_stdheap_traits->deallocate
		= &synapse_memory_mman_winheap_deallocate;
	ptr_stdheap_traits->alloc_unit
		= NULL;

	return
		ptr_stdheap_traits;
}