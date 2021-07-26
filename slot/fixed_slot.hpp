#include <memory/vmem/vmem.hpp>
#include <memory/block/block.hpp>
#include <lockfree/stack/fixed_stack.hpp>

namespace memory  {
    template <uint32_t page_count, uint32_t slot_size>
    class fixed_slot: protected lockfree::fixed_stack<memory::block, (page_count * 4096 / slot_size)>,
                      protected memory::vmem
    {
    public:
        fixed_slot();

        memory::block& acquire()                      { return this->pop(); }
        void           release(memory::block& bl_rel) { this->push(bl_rel); }
    };
}

template <uint32_t page_count, uint32_t slot_size>
memory::fixed_slot<page_count, slot_size>::fixed_slot()
    : memory::vmem(page_count)
{
    for(uint32_t bl_it = 0                      ;
        bl_it < (page_count * 4096 / slot_size) ; 
        bl_it++)                                this->push(memory::block(*this, bl_it * slot_size, slot_size));

}