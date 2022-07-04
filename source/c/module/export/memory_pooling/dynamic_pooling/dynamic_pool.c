#include <memory/pooling/dynamic/dynamic_pool.h>
#include <memory/pooling/dynamic/details/memory_pooling_dynamic_type.h>

#include <memory/module/export/memory_pooling/dynamic_pooling/dynamic_pool.h>

#include <stdlib.h>

synapse_modules_component_interface
	synapse_memory_mpool_dynamic_export
		()
{
	synapse_modules_component_interface
		hnd_interface
			= {
				.construct
					= &synapse_memory_mpool_dynamic_export_construct,
				.destruct
					= &synapse_memory_mpool_dynamic_export_destruct,
				.duplicate
					= &synapse_memory_mpool_dynamic_export_duplicate
			  };

	return
		hnd_interface;
}

void*
	synapse_memory_mpool_dynamic_export_construct
		(va_list pArgument)
{
	synapse_memory_pooling_dynamic*
		ptr_mpool_dynamic
			= malloc
				(sizeof(synapse_memory_pooling_dynamic_handle));

	 *ptr_mpool_dynamic
		= synapse_memory_pooling_dynamic_initialize
			(va_arg(pArgument, synapse_memory_mman_traits*),
			 va_arg(pArgument, size_t),
			 va_arg(pArgument, size_t));

	 return
		 ptr_mpool_dynamic;
}

void
	synapse_memory_mpool_dynamic_export_destruct
		(void* pVoidMpool)
{
	synapse_memory_pooling_dynamic_cleanup
		(*(synapse_memory_pooling_dynamic*)pVoidMpool);
	free
		(pVoidMpool);
}

void*
	synapse_memory_mpool_dynamic_export_duplicate
		(void* pVoidMpool)
{
	synapse_memory_pooling_dynamic
		*ptr_existing
			= pVoidMpool,
		*ptr_mpool
			= malloc
				(sizeof(synapse_memory_pooling_dynamic));

	*ptr_mpool
		= synapse_memory_pooling_dynamic_initialize
				(synapse_memory_opaque_cast
					((*ptr_existing), __synapse_memory_pooling_dynamic*)
						->ptr_dynamic_mman,
				 synapse_memory_opaque_cast
					((*ptr_existing), __synapse_memory_pooling_dynamic*)
						->sz_dynamic_stack_chunk,
				 synapse_memory_pooling_dynamic_current_size
					(*ptr_existing));

	return
		ptr_mpool;
}