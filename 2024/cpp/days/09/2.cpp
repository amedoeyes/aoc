#include <algorithm>
#include <bits/ranges_algo.h>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
#include <string_view>
#include <tuple>
#include <vector>

static auto parse(std::string_view buffer) {
	return buffer																									 //
				 | std::views::filter([](char c) { return c != '\n'; })	 //
				 | std::views::transform([](char c) { return c - '0'; }) //
				 | std::views::chunk(2)																	 //
				 | std::views::enumerate																 //
				 | std::views::transform([](const auto& el) {
						 static auto total_size = 0ul;
						 const auto& [id, subrange] = el;
						 auto it = subrange.begin();
						 auto size = *it;
						 auto free = (++it != subrange.end()) ? *it : 0;
						 auto pos = total_size;
						 total_size += size + free;
						 return std::make_tuple(id, pos, size, free, size);
					 }) //
				 | std::ranges::to<
					 std::vector<std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, uint64_t>>>();
}

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	auto disk = parse(buffer);
	const auto sum =
		std::ranges::fold_left(disk | std::views::reverse, 0ul, [&disk](auto acc, auto block) {
			auto& [lid, lpos, lsize, lfree, losize] = block;
			for (auto& [id, pos, size, free, osize] : disk | std::views::take(lid)) {
				if (losize > free) continue;
				const auto sum = acc + ((losize * ((pos + size) + ((pos + size) + losize - 1)) / 2) * lid);
				free -= losize;
				size += losize;
				return sum;
			}
			return acc + ((losize * (lpos + (lpos + losize - 1)) / 2) * lid);
		});

	std::println("{}", sum);
}
