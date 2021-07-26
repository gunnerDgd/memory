#pragma once
#include <memory/memory.hpp>
#include <memory/vmem/vmem.hpp>
#include <lockfree/stack/stack.hpp>

namespace memory  {
	class slot    : private lockfree::stack<memory::memory>
	{
	public:
		slot(size_t slot_memory_size = 4096,
			 size_t slot_init_size   = 1024);

	public:
		memory::memory acquire();
		void		   release(memory::memory& mp_rel);
	};
}

memory::slot::slot(size_t slot_memory_size, size_t slot_init_size)
{
	for(size_t i = 0 ; i < slot_init_size ; i++)
		this->push(memory::vmem(slot_memory_size));
}

memory::memory memory::slot::acquire() 						 { return memory::memory(this->pop()); }
void 		   memory::slot::release(memory::memory& mp_rel) { this-		   >push(mp_rel)     ; }