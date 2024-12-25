#include "file.hpp"

#include <bits/stdc++.h>

using namespace std::literals;

static auto parse(auto path) {
	auto grids = file(path).str() //
						 | std::views::split("\n\n"sv)
						 | std::views::transform([](const auto grid) { return std::string_view(grid); });
	auto locks = std::vector<std::array<int32_t, 5>>();
	auto keys = std::vector<std::array<int32_t, 5>>();
	for (const auto& grid : grids) {
		const auto is_lock = grid.starts_with("#####");
		auto column_sum = std::array<int32_t, 5>();
		for (const auto y : std::views::iota(0, 7)) {
			if ((is_lock && y == 0) || (!is_lock && y == 6)) continue;
			for (const auto x : std::views::iota(0, 5)) {
				if (grid[(y * 6) + x] == '#') ++column_sum[x];
			}
		}
		(is_lock ? locks : keys).emplace_back(column_sum);
	}
	return std::tuple{locks, keys};
}

auto main(int /*argc*/, char** argv) -> int {
	const auto [locks, keys] = parse(argv[1]);
	const auto count = std::ranges::fold_left(locks, 0, [&](const auto acc, const auto& lock) {
		return acc + std::ranges::count_if(keys, [&](const auto& key) {
						 return std::ranges::all_of(std::views::iota(0, 5), [&](const auto i) {
							 return lock[i] + key[i] <= 5;
						 });
					 });
	});
	std::println("{}", count);
}
