#include <memory/pooling/dynamic/details/memory_pooling_dynamic_alloc.h>

__synapse_memory_pooling_dynamic_chunk*
__synapse_memory_pooling_dynamic_allocate
	(__synapse_memory_pooling_dynamic* pMpool, void* pAllocHint)
{
	return
		InterlockedPopEntrySList(&pMpool->hnd_dynamic_stack);
}

void
__synapse_memory_pooling_dynamic_deallocate
	(__synapse_memory_pooling_dynamic* pMpool, __synapse_memory_pooling_dynamic_chunk* pChunk)
{
	InterlockedPushEntrySList
		(&pMpool->hnd_dynamic_stack, pChunk);
}

size_t
__synapse_memory_pooling_dynamic_expand
	(__synapse_memory_pooling_dynamic* pMpool, size_t pExpandCount)
{
	while (--pExpandCount != -1)
	{
		__synapse_memory_pooling_dynamic_chunk* ptr_chunk
			= _aligned_malloc(sizeof(__synapse_memory_pooling_dynamic_chunk), 16);

		ptr_chunk->ptr_chunk
			= synapse_memory_mman_traits_allocate
				(pMpool->ptr_dynamic_mman, NULL, pMpool->sz_dynamic_stack_chunk);
		InterlockedPushEntrySList
			(&pMpool->hnd_dynamic_stack, ptr_chunk);
	}

	return
		QueryDepthSList(&pMpool->hnd_dynamic_stack);
}

size_t
__synapse_memory_pooling_dynamic_shrink
	(__synapse_memory_pooling_dynamic* pMpool, size_t pShrinkCount)
{
	while (--pShrinkCount != -1)
	{
		__synapse_memory_pooling_dynamic_chunk* ptr_chunk;
		while (!(ptr_chunk = InterlockedPopEntrySList(&pMpool->hnd_dynamic_stack)));

		synapse_memory_mman_traits_deallocate
			(pMpool->ptr_dynamic_mman, ptr_chunk->ptr_chunk, pMpool->sz_dynamic_stack_chunk);
		_aligned_free
			(ptr_chunk);
	}

	return
		QueryDepthSList(&pMpool->hnd_dynamic_stack);
}

size_t
__synapse_memory_pooling_dynamic_current_size
	(__synapse_memory_pooling_dynamic* pMpool)
{
	return
		QueryDepthSList(&pMpool->hnd_dynamic_stack);
}