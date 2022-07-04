#include <memory/module/export/memory_pooling/static_pooling/static_pool.h>

#include <memory/pooling/static/static_pool.h>
#include <memory/pooling/static/details/memory_pooling_static_type.h>

#include <stdlib.h>
#include <string.h>

synapse_modules_component_interface
	synapse_memory_mpool_static_export
		()
{
	synapse_modules_component_interface
		hnd_interface
			= {
				.construct
					= &synapse_memory_mpool_static_export_construct,
				.destruct
					= &synapse_memory_mpool_static_export_destruct,
				.duplicate
					= &synapse_memory_mpool_static_export_duplicate
			  };

	return
		hnd_interface;
}

void*
	synapse_memory_mpool_static_export_construct
		(va_list pArgument)
{
	synapse_memory_pooling_static*
		ptr_mpool_static
			= malloc
				(sizeof(synapse_memory_pooling_static));

	 *ptr_mpool_static
		= synapse_memory_pooling_static_initialize
			(va_arg(pArgument, synapse_memory_mman_traits*),
			 va_arg(pArgument, size_t),
			 va_arg(pArgument, size_t));

	 return
		 ptr_mpool_static;
}

void
	synapse_memory_mpool_static_export_destruct
		(void* pVoidMpool)
{
	synapse_memory_pooling_static_cleanup
		(*(synapse_memory_pooling_static*)pVoidMpool);
	free
		(pVoidMpool);
}

void*
	synapse_memory_mpool_static_export_duplicate
		(void* pVoidMpool)
{
	synapse_memory_pooling_static
		*ptr_existing
			= pVoidMpool,
		*ptr_mpool
			= malloc
				(sizeof(synapse_memory_pooling_static));

	*ptr_mpool
		= synapse_memory_pooling_static_initialize
				(synapse_memory_opaque_cast
					((*ptr_existing), __synapse_memory_pooling_static*)
						->ptr_pool_mman,
				 synapse_memory_opaque_cast
					((*ptr_existing), __synapse_memory_pooling_static*)
						->sz_pooled_chunk,
				 synapse_memory_opaque_cast
					((*ptr_existing), __synapse_memory_pooling_static*)
						->sz_pooled_chunk_count);

	return
		ptr_mpool;
}