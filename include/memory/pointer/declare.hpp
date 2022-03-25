#pragma once
#include <type_traits>

namespace memory::pointer_category {
	class address_based   {};
	class external_device {};
}

namespace memory {
	template <typename T, typename U, typename V, typename R>
	class basic_access_pointer;

	inline constexpr pointer_category::external_device external_device;
	inline constexpr pointer_category::address_based   address_based  ;
}