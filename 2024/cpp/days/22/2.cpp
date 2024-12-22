#include "file.hpp"

#include <bits/stdc++.h>

static auto parse(auto path) {
	return file(path).str() //
			 | std::views::split('\n') //
			 | std::views::filter([](auto line) { return !line.empty(); })
			 | std::views::transform([](auto line) {
					 int64_t n = 0;
					 std::from_chars(line.data(), line.data() + line.size(), n);
					 return n;
				 })
			 | std::ranges::to<std::vector<uint64_t>>();
}

struct hash {
	auto operator()(const auto& tuple) const -> size_t {
		auto [a, b, c, d] = tuple;
		a ^= b + 0x9e3779b9 + (a << 6u) + (a >> 2u);
		a ^= c + 0x9e3779b9 + (a << 6u) + (a >> 2u);
		a ^= d + 0x9e3779b9 + (a << 6u) + (a >> 2u);
		return a;
	}
};

auto main(int /*argc*/, char** argv) -> int {
	const auto secrets = parse(argv[1]);
	auto cache = std::unordered_map<std::tuple<int64_t, int64_t, int64_t, int64_t>, int64_t, hash>();
	for (auto secret : secrets) {
		auto visited = std::unordered_set<std::tuple<int64_t, int64_t, int64_t, int64_t>, hash>();
		const auto prices = std::views::iota(0, 2000) | std::views::transform([&](auto) {
													secret = ((secret << 6u) ^ secret) & 0xFFFFFFu;
													secret = ((secret >> 5u) ^ secret) & 0xFFFFFFu;
													secret = ((secret << 11u) ^ secret) & 0xFFFFFFu;
													return secret % 10;
												})
											| std::ranges::to<std::vector<int64_t>>();
		const auto diffs = prices | std::views::adjacent<2> | std::views::transform([](auto p) {
												 return std::get<1>(p) - std::get<0>(p);
											 });
		for (const auto& [i, seq] : diffs | std::views::adjacent<4> | std::views::enumerate) {
			if (visited.contains(seq)) continue;
			visited.emplace(seq);
			cache[seq] += prices[i + 4];
		}
	}
	const auto max = std::ranges::max(cache | std::views::values);
	std::println("{}", max);
}
