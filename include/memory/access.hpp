#pragma once
#include <type_traits>

namespace memory::access {
	template <std::size_t Start, std::size_t End>
	struct region
	{
		static constexpr std::size_t start = Start;
		static constexpr std::size_t end   = End  ;
	};

	using all_region = region<-1, -1>;

	template <typename AccessType, typename RegionType = all_region>
	struct read_only
	{ 
		typedef AccessType type;
		typedef RegionType access_region;

		static constexpr std::size_t start = access_region::start;
		static constexpr std::size_t end   = access_region::end  ;

		template <typename NewRegion>
		constexpr auto operator|(NewRegion&&) { return read_only <AccessType, std::decay_t<NewRegion>>{}; }
	};

	template <typename AccessType, typename RegionType = all_region>
	struct write_only
	{
		typedef AccessType type;
		typedef RegionType access_region;

		static constexpr std::size_t start = access_region::start;
		static constexpr std::size_t end   = access_region::end  ;

		template <typename NewRegion>
		constexpr auto operator|(NewRegion&&) { return write_only<AccessType, std::decay_t<NewRegion>>{}; }
	};

	template <typename T>
	struct start { };

	template <typename T, typename R>
	struct start<read_only <T, R>> { static constexpr std::size_t value = R::start; };

	template <typename T, typename R>
	struct start<write_only<T, R>> { static constexpr std::size_t value = R::start; };

	template <typename T>
	struct end { };

	template <typename T, typename R>
	struct end<read_only <T, R>> { static constexpr std::size_t value = R::end; };

	template <typename T, typename R>
	struct end<write_only<T, R>> { static constexpr std::size_t value = R::end; };

	template <typename T>
	inline constexpr std::size_t start_v = start<T>;
	template <typename T>
	inline constexpr std::size_t end_v   = end<T>  ;
}