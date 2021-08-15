#include <cstdint>

namespace memory {

    enum state { free, allocated, reserved };

    template <typename memory_data_t, typename memory_controller_t>
    class memory
    {
    public:
        memory ();
        memory (typename memory_controller_t::memory_prot_t prot, void* adjoin = nullptr);
        ~memory()                                                                        { this->deallocate(); }

    public:
        memory_data_t*                                allocate   (typename memory_controller_t::memory_prot_t prot, void* adjoin = nullptr);
        typename memory_controller_t::memory_result_t deallocate ();

    public:
        memory_data_t*                                reserve    (void* adjoin = nullptr);
        typename memory_controller_t::memory_result_t commit     (typename memory_controller_t::memory_prot_t prot);

    public:
        memory_data_t*                                get_pointer() { return memory_pointer; }

    protected:
        memory_data_t*                                memory_pointer;
        state                                         memory_state  ;
    };
}

template <typename memory_data_t, typename memory_controller_t>
memory::memory<memory_data_t, memory_controller_t>::memory ()
    : memory_state(state::free) { }

template <typename memory_data_t, typename memory_controller_t>
memory::memory<memory_data_t, memory_controller_t>::memory (typename memory_controller_t::memory_prot_t prot, void* adjoin)
    : memory_pointer(this->allocate(prot, adjoin)) { }

template <typename memory_data_t, typename memory_controller_t>
memory_data_t* memory::memory<memory_data_t, memory_controller_t>::allocate(typename memory_controller_t::memory_prot_t prot, void* adjoin)
{
    if(memory_state != state::free)
        return nullptr;
    else
    {
        auto allocate_res = (memory_pointer = (memory_data_t*)memory_controller_t::allocate(prot, sizeof(memory_data_t), adjoin));
        if  (allocate_res)
            memory_state = state::allocated;
        
        return allocate_res;
    }
}

template <typename memory_data_t, typename memory_controller_t>
typename memory_controller_t::memory_result_t memory::memory<memory_data_t, memory_controller_t>::deallocate ()
{
    if(memory_state != state::free)
        return memory_controller_t::deallocate(sizeof(memory_data_t), memory_pointer);
    else
        return 0;
}

template <typename memory_data_t, typename memory_controller_t>
memory_data_t* memory::memory<memory_data_t, memory_controller_t>::reserve    (void* adjoin)
{
    if(memory_state == state::free)
        return memory_controller_t::reserve(sizeof(memory_data_t), adjoin);
    else
        return nullptr;
}

template <typename memory_data_t, typename memory_controller_t>
typename memory_controller_t::memory_result_t memory::memory<memory_data_t, memory_controller_t>::commit     (typename memory_controller_t::memory_prot_t prot)
{
    if(memory_state == state::reserved)
        return memory_controller_t::commit(prot, sizeof(memory_data_t), memory_pointer);
    else
        return -1;
}