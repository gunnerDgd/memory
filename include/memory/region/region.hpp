#pragma once
#include <type_traits>

namespace memory::region {
	template <std::size_t Begin, std::size_t End>
	struct region 
	{
		static constexpr std::size_t begin = Begin;
		static constexpr std::size_t end   = End  ;
	};

	template <typename InputRegion>
	struct begin { static constexpr std::size_t value = InputRegion::begin; };

	template <typename InputRegion>
	struct end   { static constexpr std::size_t value = InputRegion::end  ; };

	template <typename InputRegion>
	inline constexpr std::size_t begin_v = begin<InputRegion>::value;

	template <typename InputRegion>
	inline constexpr std::size_t end_v   = begin<InputRegion>::end  ;
}

template <typename LRegion, typename RRegion>
auto operator|(LRegion lhs, RRegion rhs)
{
	return memory::region::region<(memory::region::begin_v<LRegion> < memory::region::begin_v<RRegion>)
								 ? memory::region::begin_v<LRegion> : memory::region::begin_v<RRegion>,
								  (memory::region::end_v<LRegion> > memory::region::end_v<RRegion>
								 ? memory::region::end_v<LRegion> : memory::region::end_v<RRegion>)>  {  };
}

