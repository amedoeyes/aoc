#include <algorithm>
#include <cctype>
#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

constexpr auto to_int = [](const std::ranges::view auto& str) {
	int64_t n = 0;
	std::from_chars(str.data(), str.data() + str.size(), n);
	return n;
};

static auto parse_rule(std::string_view line) -> std::pair<int64_t, int64_t> {
	auto parts = line											//
							 | std::views::split('|') //
							 | std::views::transform(to_int);
	auto it = parts.begin();
	return {*it, *(++it)};
}

static auto parse_update(std::string_view line) -> std::vector<int64_t> {
	return line														 //
				 | std::views::split(',')				 //
				 | std::views::transform(to_int) //
				 | std::ranges::to<std::vector<int64_t>>();
}

auto main(int /*argc*/, char** argv) -> int {
	std::ifstream file(argv[1]);

	int64_t sum = 0;
	bool rules_section = true;
	std::unordered_map<int64_t, std::unordered_set<int64_t>> rules;
	for (std::string line; std::getline(file, line);) {
		if (line.empty()) {
			rules_section = false;
			continue;
		}
		if (rules_section) {
			const auto [a, b] = parse_rule(line);
			rules[a].insert(b);
			continue;
		}
		const auto cmp = [&rules](int64_t a, int64_t b) {
			return rules[a].contains(b);
		};
		auto update = parse_update(line);
		if (!std::ranges::is_sorted(update, cmp)) {
			std::ranges::sort(update, cmp);
			sum += update[update.size() / 2];
		}
	}

	std::println("{}", sum);

	return 0;
}
