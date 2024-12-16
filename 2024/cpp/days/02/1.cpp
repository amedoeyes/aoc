#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
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

auto in_range(int64_t n) -> bool {
	int64_t const abs = std::abs(n);
	return abs >= 1 && abs <= 3;
};

auto same_sign(int64_t a, int64_t b) -> bool {
	return a * b > 0;
};

auto main(int /*argc*/, char** argv) -> int {
	std::ifstream file(argv[1]);

	int64_t safe_reports = 0;
	for (std::string line; std::getline(file, line);) {
		const std::vector<int64_t> diffs = parse_line(line)					 //
																			 | std::views::adjacent<2> //
																			 | std::views::transform([](auto pair) {
																					 return std::get<0>(pair) - std::get<1>(pair);
																				 }) //
																			 | std::ranges::to<std::vector<int64_t>>();
		uint64_t left = 0;
		for (size_t i = 0; i < diffs.size(); ++i) {
			if (!in_range(diffs[i]) || (i != 0 && !same_sign(diffs[i], diffs[i - 1]))) {
				break;
			}
			++left;
		}
		if (left == diffs.size()) {
			++safe_reports;
			continue;
		}
	}

	std::println("{}", safe_reports);

	return 0;
}
