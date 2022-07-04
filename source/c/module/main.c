#include <memory/module/main.h>

#include <memory/module/export/stdheap.h>
#include <memory/module/export/winheap.h>

#include <memory/module/export/memory_pooling/static_pooling/static_pool.h>

#include <string.h>

static synapse_modules_handle
			__synapse_memory_module_handle;
static synapse_modules_component_interface_handle
			__synapse_memory_module_stdheap_interface,
			__synapse_memory_module_winheap_interface;

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
				(hnd_compman, synapse_memory_mman_stdheap_export(), "standard_heap");
	__synapse_memory_module_winheap_interface
		= synapse_modules_component_manager_register_interface
				(hnd_compman, synapse_memory_mman_winheap_export(), "windows-heap");
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