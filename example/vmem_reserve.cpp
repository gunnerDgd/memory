#include <memory/vmem/vmem.hpp>

int main()
{
    memory::reserved_vmem test_vmem_reserved;
    std::cout << test_vmem_reserved.memory_pointer() << std::endl;
    
    memory::vmem           test_vmem(test_vmem_reserved);
    std::cout << test_vmem.memory_pointer() << std::endl;
}