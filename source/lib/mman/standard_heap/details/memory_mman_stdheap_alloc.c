#include <memory/mman/standard_heap/details/memory_mman_stdheap_alloc.h>
#include <memory/export/memory.h>

#include <memory/system/allocation/system_allocate.h>

void*
	__synapse_memory_mman_stdheap_allocate
		(__synapse_memory_mman_stdheap_head* pHead, void* pHint, size_t pSize)
{
	__synapse_memory_mman_stdheap*
		ptr_alloc
			= malloc
				(NULL, sizeof(__synapse_memory_mman_stdheap) + pSize);

	ptr_alloc->stdheap_alloc_head 
		= pHead;
	ptr_alloc->stdheap_prev 
		= pHead->ptr_back;
	ptr_alloc->stdheap_next 
		= NULL;

	if (!pHead->ptr_back) {
		pHead->ptr_back
			= (pHead->ptr_head = ptr_alloc);
	}
	else {
		pHead->ptr_back->stdheap_next
			= ptr_alloc;
		ptr_alloc->stdheap_prev
			= pHead->ptr_back;
		
		pHead->ptr_back
			= ptr_alloc;
	}

	return
		(uint8_t*)ptr_alloc
				+ sizeof(__synapse_memory_mman_stdheap);
}

void
	__synapse_memory_mman_stdheap_deallocate
		(__synapse_memory_mman_stdheap_head* pHead, 
			__synapse_memory_mman_stdheap  * pHeap)
{
	if (pHeap->stdheap_alloc_head != pHead)
		return;

	if(pHeap->stdheap_prev)
		pHeap->stdheap_prev->stdheap_next
			= pHeap->stdheap_next;
	else
		pHead->ptr_head
			= pHeap->stdheap_next;

	if(pHeap->stdheap_next)
		pHeap->stdheap_next->stdheap_prev
			= pHeap->stdheap_prev;
	else
		pHead->ptr_back
			= pHeap->stdheap_prev;

	free
		(pHeap);
}

void
	__synapse_memory_mman_stdheap_deallocate_all
		(__synapse_memory_mman_stdheap_head* pHead)
{
	__synapse_memory_mman_stdheap*
		ptr_seek
			= pHead->ptr_head;

	while(ptr_seek)
	{
		__synapse_memory_mman_stdheap*
			ptr_dealloc
				= ptr_seek;

		ptr_seek
			= ptr_seek->stdheap_next;

		free
			(ptr_dealloc);
	}
}