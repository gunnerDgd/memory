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
	synapse_memory_pooling_static_traits*
		ptr_mpool
			= malloc
				(sizeof(synapse_memory_pooling_static_traits));

	 ptr_mpool->hnd_traits
		= synapse_memory_pooling_static_initialize
			(va_arg(pArgument, synapse_memory_mman_traits*),
			 va_arg(pArgument, size_t),
			 va_arg(pArgument, size_t));

	 ptr_mpool->allocate
		 = &synapse_memory_pooling_static_allocate;
	 ptr_mpool->deallocate
		 = &synapse_memory_pooling_static_deallocate;
	 ptr_mpool->retrieve_pointer
		 = &synapse_memory_pooling_static_retrieve_pointer;

	 return
		 ptr_mpool;
}

void
	synapse_memory_mpool_static_export_destruct
		(void* pVoidMpool)
{
	synapse_memory_pooling_static_traits*
		ptr_traits
			= pVoidMpool;

	synapse_memory_pooling_static_cleanup
		(ptr_traits->hnd_traits);
	free
		(pVoidMpool);
}

void*
	synapse_memory_mpool_static_export_duplicate
		(void* pVoidMpool)
{
	synapse_memory_pooling_static_traits
		*ptr_existing
			= pVoidMpool,
		*ptr_mpool
			= malloc
				(sizeof(synapse_memory_pooling_static_traits));

	ptr_mpool->hnd_traits
		= synapse_memory_pooling_static_initialize
				(synapse_memory_opaque_cast
					(ptr_existing->hnd_traits, __synapse_memory_pooling_static*)
						->ptr_pool_mman,
				 synapse_memory_opaque_cast
					(ptr_existing->hnd_traits, __synapse_memory_pooling_static*)
						->sz_pooled_chunk,
				 synapse_memory_opaque_cast
					(ptr_existing->hnd_traits, __synapse_memory_pooling_static*)
						->sz_pooled_chunk_count);

	ptr_mpool->allocate
		= &synapse_memory_pooling_static_allocate;
	ptr_mpool->deallocate
		= &synapse_memory_pooling_static_deallocate;
	ptr_mpool->retrieve_pointer
		= &synapse_memory_pooling_static_retrieve_pointer;

	return
		ptr_mpool;
}