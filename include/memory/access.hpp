#pragma once
#include <type_traits>

namespace memory::access {
	template <typename AccessType>
	class read_only  { typedef AccessType type; };

	template <typename AccessType>
	class write_only { typedef AccessType type; };

	template <typename AccessType>
	class all        { typedef AccessType type; };
}