#include <memory/mman/standard_heap/stdheap_alloc.h>
#include <memory/mman/standard_heap/details/memory_mman_stdheap_alloc.h>

synapse_memory_block
synapse_memory_mman_stdheap_allocate
	(synapse_memory_manager_handle pMman, void* pHint, size_t pSize)
{
	synapse_memory_opaque_init
		(synapse_memory_block, hnd_block,
			__synapse_memory_mman_stdheap_allocate
				(synapse_memory_opaque_reference(pMman), pHint, pSize));

	return
		hnd_block;
}

void
synapse_memory_mman_stdheap_deallocate
	(synapse_memory_manager_handle pMman, synapse_memory_block pBlock)
{
	__synapse_memory_mman_stdheap_deallocate
		(synapse_memory_opaque_reference(pMman),
		 synapse_memory_opaque_reference(pBlock));
}

void
synapse_memory_mman_stdheap_deallocate_all
	(synapse_memory_manager_handle pHeap)
{
	__synapse_memory_mman_stdheap_deallocate_all
		(synapse_memory_opaque_reference(pHeap));
}

void*
	synapse_memory_mman_stdheap_block_pointer
		(synapse_memory_block pBlock)
{
	return
		synapse_memory_opaque_cast
			(pBlock, __synapse_memory_mman_stdheap*)
				->stdheap_ptr;
}

size_t
	synapse_memory_mman_stdheap_block_size
		(synapse_memory_block pBlock)
{
	return
		synapse_memory_opaque_cast
			(pBlock, __synapse_memory_mman_stdheap*)
				->stdheap_size;
}