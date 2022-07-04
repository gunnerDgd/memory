#pragma once
#include <modules/traits/modman_interface.h>
#include <memory/mman/mman_traits.h>

synapse_modules_component_interface
	synapse_memory_mman_winheap_export
		();

void*
	synapse_memory_mman_winheap_export_construct
		(va_list);

void
	synapse_memory_mman_winheap_export_destruct
		(void*);

void*
	synapse_memory_mman_winheap_export_duplicate
		(void*);