#pragma once
#include <modules/traits/modman_interface.h>
#include <memory/pooling/static_pooling_traits.h>

synapse_modules_component_interface
	synapse_memory_mpool_static_export
		();

void*
	synapse_memory_mpool_static_export_construct
		(va_list);

void
	synapse_memory_mpool_static_export_destruct
		(void*);

void*
	synapse_memory_mpool_static_export_duplicate
		(void*);