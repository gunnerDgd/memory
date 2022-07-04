#include <memory/module/export/stdheap.h>

#include <memory/mman/standard_heap/stdheap.h>
#include <memory/mman/standard_heap/details/memory_mman_stdheap_type.h>

#include <stdlib.h>

synapse_modules_component_interface
	synapse_memory_mman_stdheap_export
		()
{
	synapse_modules_component_interface
		hnd_interface
			= {
				.construct
					= &synapse_memory_mman_stdheap_export_construct,
				.destruct
					= &synapse_memory_mman_stdheap_export_destruct ,
				.duplicate
					= &synapse_memory_mman_stdheap_export_duplicate
			  };

	return
		hnd_interface;
}

void*
synapse_memory_mman_stdheap_export_construct
	(va_list pInitArgs)
{
	synapse_memory_mman_stdheap*
		ptr_stdheap_handle
			= malloc(sizeof(synapse_memory_mman_stdheap));
		
	*ptr_stdheap_handle
		= synapse_memory_mman_stdheap_initialize
				(va_arg(pInitArgs, size_t));

	return
		ptr_stdheap_handle;
}

void
	synapse_memory_mman_stdheap_export_destruct
		(void* pVoidStdHeap)
{
	synapse_memory_mman_stdheap_cleanup
		(*(synapse_memory_mman_stdheap*)pVoidStdHeap);
	free
		(pVoidStdHeap);
}

void*
	synapse_memory_mman_stdheap_export_duplicate
		(void* pVoidStdHeap)
{
	synapse_memory_mman_stdheap*
		ptr_stdheap_handle
			= malloc(sizeof(synapse_memory_mman_stdheap));
		
	*ptr_stdheap_handle
		= synapse_memory_mman_stdheap_initialize
				(((__synapse_memory_mman_stdheap*)pVoidStdHeap)
					->sz_stdheap_alloc_unit);

	return
		ptr_stdheap_handle;
}