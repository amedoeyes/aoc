#include "file.hpp"

#include <bits/stdc++.h>

static auto parse(auto path) {
	const auto buffer = file(path).str();
	auto parts = buffer | std::views::split(std::string_view("\n\n"));
	auto it = parts.begin();
	auto patterns = *it //
								| std::views::split(std::string_view(", "))
								| std::ranges::to<std::vector<std::string>>();
	const auto designs = *++it //
										 | std::views::split('\n')
										 | std::views::filter([](auto line) { return !line.empty(); })
										 | std::ranges::to<std::vector<std::string>>();
	return std::pair(patterns, designs);
}

auto main(int /*argc*/, char** argv) -> int {
	const auto [patterns, designs] = parse(argv[1]);
	auto cache = std::unordered_map<std::string, int64_t>({{"", 1}});
	auto solve = std::function<int64_t(std::string)>();
	solve = [&](const auto& d) {
		if (cache.contains(d)) return cache[d];
		auto count = 0l;
		for (const auto& p : patterns) {
			if (d.starts_with(p)) count += solve(d.substr(p.size()));
		}
		cache[d] = count;
		return count;
	};
	auto count = 0l;
	for (const auto& design : designs) count += solve(design);
	std::println("{}", count);
}
