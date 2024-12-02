#include <algorithm>
#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

auto parse_line(std::string_view line) -> std::vector<int64_t> {
	return line											//
				 | std::views::split(' ') //
				 | std::views::transform([](auto&& level) {
						 int64_t l = 0;
						 std::from_chars(level.data(), level.data() + level.size(), l);
						 return l;
					 }) //
				 | std::ranges::to<std::vector<int64_t>>();
}

auto is_safe(std::span<const int64_t> levels) -> bool {
	auto pairs = levels | std::views::adjacent<2>;
	bool const is_inc = std::ranges::all_of(pairs, [](std::tuple<int64_t, int64_t> pair) {
		return std::get<0>(pair) < std::get<1>(pair);
	});
	bool const is_dec = std::ranges::all_of(pairs, [](std::tuple<int64_t, int64_t> pair) {
		return std::get<0>(pair) > std::get<1>(pair);
	});
	bool const valid_diff = std::ranges::all_of(pairs, [](std::tuple<int64_t, int64_t> pair) {
		return std::abs(std::get<0>(pair) - std::get<1>(pair)) <= 3;
	});
	return (is_inc || is_dec) && valid_diff;
}

auto main(int /*argc*/, char** argv) -> int {
	std::ifstream file(argv[1]);

	int64_t safe_reports = 0;
	for (std::string line; std::getline(file, line);) {
		const std::vector<int64_t> levels = parse_line(line);
		if (is_safe(levels)) {
			++safe_reports;
		}
	}

	std::println("{}", safe_reports);

	return 0;
}
