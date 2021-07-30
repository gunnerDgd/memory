#include <memory/memory.hpp>
#include <io/io.hpp>

namespace memory {

    io::io& operator << (io::io& w_device, memory& w_memory, size_t w_size = 0)
    {
        if(w_memory.memory_size() < w_size) IO_HANDLE_IO_ERROR(w_device, "Error While Memory I/O", w_device);
        
        size_t w_res  =    w_device.read     (w_memory.memory_pointer()         , (w_size == 0) ? w_memory.memory_size() : w_size);
        if    (w_res == 0) IO_HANDLE_IO_ERROR(w_device, "Error While Memory I/O", w_device);
        else               IO_HANDLE_SUCCESS (w_device);
    }
    
    io::io& operator >> (io::io& r_device, memory& r_memory, size_t r_size = 0)
    {
        if(r_memory.memory_size() < r_size) IO_HANDLE_IO_ERROR(r_device, "Error While Memory I/O", r_device);
        
        size_t r_res  =    r_device.read     (r_memory.memory_pointer()         , (r_size == 0) ? r_memory.memory_size() : r_size);
        if    (r_res == 0) IO_HANDLE_IO_ERROR(r_device, "Error While Memory I/O", r_device);
        else               IO_HANDLE_SUCCESS (r_device);
    }

}