#include <memory/module/main.h>

#include <memory/module/export/stdheap.h>
#include <memory/module/export/winheap.h>

#include <memory/module/export/memory_pooling/static_pooling/static_pool.h>
#include <memory/module/export/memory_pooling/dynamic_pooling/dynamic_pool.h>

#include <string.h>

static synapse_modules_handle
			__synapse_memory_module_handle;
static synapse_modules_component_interface_handle
			__synapse_memory_module_stdheap_interface,
			__synapse_memory_module_winheap_interface,
	
			__synapse_memory_module_mpool_static,
			__synapse_memory_module_mpool_dynamic;

static synapse_memory_mman_traits
			__synapse_memory_module_mman_typedata;
static synapse_memory_pooling_static_traits
			__synapse_memory_module_mpool_static_typedata;
static synapse_memory_pooling_dynamic_traits
			__synapse_memory_module_mpool_dynamic_typedata;

synapse_modules_export
void
synapse_memory_module_attach
	(synapse_modules_handle pHandle)
{
	synapse_modules_component_manager hnd_compman
		= synapse_modules_modman_module_retrieve_component_manager
			(pHandle);
	__synapse_memory_module_handle
		= pHandle;

	__synapse_memory_module_stdheap_interface
		= synapse_modules_component_manager_register_interface
				(hnd_compman, synapse_memory_mman_stdheap_export(), "standard_heap",
					&__synapse_memory_module_mman_typedata);
	__synapse_memory_module_winheap_interface
		= synapse_modules_component_manager_register_interface
				(hnd_compman, synapse_memory_mman_winheap_export(), "windows_heap",
					&__synapse_memory_module_mman_typedata);

	__synapse_memory_module_mpool_static
		= synapse_modules_component_manager_register_interface
				(hnd_compman, synapse_memory_mpool_static_export(), "static_pool",
					&__synapse_memory_module_mpool_static_typedata);
	__synapse_memory_module_mpool_dynamic
		= synapse_modules_component_manager_register_interface
				(hnd_compman, synapse_memory_mpool_dynamic_export(), "dynamic_pool",
					&__synapse_memory_module_mpool_dynamic_typedata);
}

synapse_modules_export
void
synapse_modules_initialize
	(synapse_modules_interface* pInterface)
{
	strcpy
		(pInterface->modules_name, "synapse-memory-mman");
}

synapse_modules_export
void
	synpase_modules_cleanup
		()
{
}