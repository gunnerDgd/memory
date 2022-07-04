#pragma once
#include <modules/traits/modman_interface.h>
#include <modules/defines/export.h>

#include <modules/component/component.h>
#include <modules/modman/modman.h>

synapse_modules_export
	void
		synapse_memory_module_attach
			(synapse_modules_handle);

synapse_modules_export
void
	synapse_modules_initialize
		(synapse_modules_interface*);

synapse_modules_export
void
	synpase_modules_cleanup
		();