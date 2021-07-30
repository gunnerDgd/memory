#define VMEM_HANDLE_MMAP_FAILED(memory, message)              \
{                                                             \
    memory.set_state(memory_state::allocate_error);           \
    std::cout << "## ERROR ## [Memory] : " << message << '\n';\
}                                                             \

#define VMEM_HANDLE_MPROTECT_FAILED(memory)                   \
    VMEM_HANDLE_MMAP_FAILED(memory, "MPROTECT Failed.")       \

#define VMEM_HANDLE_MNUMAP_FAILED                          \
    std::cout << "## ERROR ## [Memory] : MNUMAP Failed.\n";\
    exit(1);                                               \