#pragma once
#include <memory/defines/opaque/opaque.h>
#include <Windows.h>

typedef struct __synapse_memory_mman_winheap
{
	HANDLE
		hnd_wheap;
	size_t
		sz_wheap_init,
		sz_wheap_max ;
} __synapse_memory_mman_winheap;