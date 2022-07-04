#pragma once
#include <modules/traits/modman_interface.h>
#include <memory/pooling/dynamic_pooling_traits.h>

synapse_modules_component_interface
	synapse_memory_mpool_dynamic_export
		();

void*
	synapse_memory_mpool_dynamic_export_construct
		(va_list);

void
	synapse_memory_mpool_dynamic_export_destruct
		(void*);

void*
	synapse_memory_mpool_dynamic_export_duplicate
		(void*);