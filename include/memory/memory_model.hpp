#pragma once
#include <memory/basic_memory_model.hpp>

#include <memory/traits/virtual_memory.hpp>
#include <memory/access/virtual_memory.hpp>

#include <memory/traits/io_map.hpp>
#include <memory/access/io_map.hpp>

namespace memory::model {
	using virtual_memory = memory::basic_memory_model<memory::virtual_memory, memory::access::virtual_memory>;
	using io_map		 = memory::basic_memory_model<memory::io_map		, memory::access::io_map>;
}