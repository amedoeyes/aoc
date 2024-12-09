#include <algorithm>
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

static auto parse(std::string_view buffer) -> std::vector<std::tuple<uint64_t, int64_t, int64_t>> {
	return buffer																									 //
				 | std::views::filter([](char c) { return c != '\n'; })	 //
				 | std::views::transform([](char c) { return c - '0'; }) //
				 | std::views::chunk(2)																	 //
				 | std::views::enumerate																 //
				 | std::views::transform([](const auto& el) {
						 const auto& [id, subrange] = el;
						 auto it = subrange.begin();
						 int64_t size = *it;
						 int64_t free = (++it != subrange.end()) ? *it : 0;
						 return std::make_tuple(id, size, free);
					 }) //
				 | std::ranges::to<std::vector<std::tuple<uint64_t, int64_t, int64_t>>>();
}

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	auto disk = parse(buffer);
	auto last = disk.size() - 1;
	auto pos = 0ul;
	const auto sum = std::ranges::fold_left(disk, 0ul, [&disk, &pos, &last](auto acc, auto block) {
		auto& [id, size, free] = block;
		auto sum = (size * (pos + (pos + size - 1)) / 2) * id;
		pos += size;
		if (free == 0) return acc + sum;
		for (auto& [lid, lsize, lfree] :
				 disk | std::views::drop(id + 1) | std::views::take(last + 1) | std::views::reverse) {
			while (lsize > 0 && free > 0) {
				sum += pos * lid;
				++pos;
				--lsize;
				--free;
			}
			if (lsize == 0) --last;
			if (free == 0) break;
		}
		return acc + sum;
	});

	std::println("{}", sum);
}
