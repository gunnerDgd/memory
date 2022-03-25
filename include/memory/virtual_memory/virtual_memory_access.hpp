#pragma once
#include <type_traits>
#include <Windows.h>

namespace memory::details {
	struct vmem_access_trait  {};
	
	struct vmem_rdonly  : public vmem_access_trait { static constexpr uint32_t value = PAGE_READONLY; };
	struct vmem_wronly  : public vmem_access_trait { static constexpr uint32_t value = 0; };
	
	struct vmem_execute : public vmem_access_trait { static constexpr uint32_t value = PAGE_EXECUTE  ; };
	struct vmem_all		: public vmem_access_trait { static constexpr uint32_t value = PAGE_READWRITE; };

	template <uint32_t Option> 
	struct vmem_accessmode						   { static constexpr uint32_t value = Option; };
}

namespace memory::access::virtual_memory {
	inline constexpr details::vmem_rdonly  read_only ;
	inline constexpr details::vmem_wronly  write_only;
	inline constexpr details::vmem_all     all		 ;
	inline constexpr details::vmem_execute executable;
}

template <typename VmemOption, typename VmemAccessMode>
std::enable_if_t<std::is_base_of_v<memory::details::vmem_access_trait, VmemOption>,
								   memory::details::vmem_accessmode<VmemOption::value | VmemAccessMode::value>>
	operator|(VmemAccessMode, VmemOption) { return memory::details::vmem_accessmode<VmemOption::value | VmemAccessMode::value>{}; }

template <typename VmemOption, typename VmemAccessMode>
std::enable_if_t<std::is_base_of_v<memory::details::vmem_access_trait, VmemOption>,
								   memory::details::vmem_accessmode<VmemOption::value & VmemAccessMode::value>>
	operator&(VmemAccessMode, VmemOption) { return memory::details::vmem_accessmode<VmemOption::value & VmemAccessMode::value>{}; }

template <typename VmemOption, typename VmemAccessMode>
std::enable_if_t<std::is_base_of_v<memory::details::vmem_access_trait, VmemOption>,
								   memory::details::vmem_accessmode<VmemOption::value ^ VmemAccessMode::value>>
	operator^(VmemAccessMode, VmemOption) { return memory::details::vmem_accessmode<VmemOption::value ^ VmemAccessMode::value>{}; }

