#include "file.hpp"

#include <bits/stdc++.h>

static auto parse(auto path) {
	const auto buffer = file(path).str();
	auto parts = buffer | std::views::split(std::string_view("\n\n"));
	auto it = parts.begin();
	auto patterns = *it //
								| std::views::split(std::string_view(", "))
								| std::ranges::to<std::vector<std::string>>();
	const auto designs = *++it//
										 | std::views::split('\n')
										 | std::views::filter([](auto line) { return !line.empty(); })
										 | std::ranges::to<std::vector<std::string>>();
	return std::pair(patterns, designs);
}

auto main(int /*argc*/, char** argv) -> int {
	const auto [patterns, designs] = parse(argv[1]);
	auto count = 0;
	for (const auto& d : designs) {
		auto stack = std::stack<std::string_view>({d});
		while (!stack.empty()) {
			const auto d = stack.top();
			stack.pop();
			if (d.empty()) {
				++count;
				break;
			}
			for (const auto& p : patterns) {
				if (d.starts_with(p)) stack.emplace(d.substr(p.size()));
			}
		}
	}
	std::println("{}", count);
}
