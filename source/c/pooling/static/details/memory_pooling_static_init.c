#include <memory/pooling/static/details/memory_pooling_static_init.h>

__synapse_memory_pooling_static*
__synapse_memory_pooling_static_initialize
	(synapse_memory_mman_traits* pMman, size_t pChunkSize, size_t pChunkCount)
{
	__synapse_memory_pooling_static* ptr_mpool
		= malloc(sizeof(__synapse_memory_pooling_static));

	InitializeSListHead
		(&ptr_mpool->hnd_pool_stack);
	
	ptr_mpool->ptr_pooled_memory
		= synapse_memory_mman_traits_allocate(pMman, NULL, pChunkSize * pChunkCount);
	ptr_mpool->ptr_pool_mman
		= pMman;
	
	ptr_mpool->sz_pooled_chunk
		= pChunkSize; 
	ptr_mpool->sz_pooled_chunk_count
		= pChunkCount;

	ptr_mpool->ptr_pooled_memory_begin
		= ptr_mpool->ptr_pooled_memory;
	ptr_mpool->ptr_pooled_memory_end
		= ptr_mpool->ptr_pooled_memory_begin + pChunkSize * pChunkCount;

	while (--pChunkCount != -1)
	{
		__synapse_memory_pooling_static_chunk* ptr_chunk
			= _aligned_malloc(sizeof(__synapse_memory_pooling_static_chunk), 16);

		ptr_chunk->chk_ptr
			= ptr_mpool->ptr_pooled_memory_begin + ptr_mpool->sz_pooled_chunk * pChunkCount;
		InterlockedPushEntrySList
			(&ptr_mpool->hnd_pool_stack, &ptr_chunk->chk_slist_hnd);
	}

	return
		ptr_mpool;
}

void
__synapse_memory_pooling_static_cleanup
	(__synapse_memory_pooling_static* pMpool)
{
	for(__synapse_memory_pooling_static_chunk
			*ptr_chunk = InterlockedPopEntrySList(&pMpool->hnd_pool_stack) ; 
			 ptr_chunk;
			 ptr_chunk = InterlockedPopEntrySlist(&pMpool->hnd_pool_stack))
		_aligned_free(ptr_chunk);

	synapse_memory_mman_traits_deallocate
		(pMpool->ptr_pool_mman, pMpool->ptr_pooled_memory, pMpool->sz_pooled_chunk * pMpool->sz_pooled_chunk_count);
	free
		(pMpool);
}