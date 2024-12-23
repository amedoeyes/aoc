#include "file.hpp"

#include <bits/stdc++.h>

static auto parse(auto path) {
	const auto pairs = file(path).str() //
									 | std::views::split('\n') //
									 | std::views::filter([](auto line) { return !line.empty(); })
									 | std::views::transform([](auto line) {
											 auto parts = line | std::views::split('-');
											 return std::pair{
												 *parts.begin() | std::ranges::to<std::string>(),
												 *++parts.begin() | std::ranges::to<std::string>()
											 };
										 })
									 | std::ranges::to<std::vector>();
	auto graph = std::unordered_map<std::string, std::unordered_set<std::string>>();
	for (const auto& [from, to] : pairs) {
		graph[from].emplace(to);
		graph[to].emplace(from);
	}
	return graph;
}

static auto solve(const auto& graph, auto& current, auto& remaining, auto& max) {
	if (remaining.empty()) {
		if (current.size() > max.size()) max = current;
		return;
	}
	while (!remaining.empty()) {
		const auto node = remaining.back();
		remaining.pop_back();
		auto new_remaining =
			remaining | std::views::filter([&](const auto& n) { return graph.at(node).contains(n); })
			| std::ranges::to<std::vector>();
		current.push_back(node);
		solve(graph, current, new_remaining, max);
		current.pop_back();
	}
}

auto main(int /*argc*/, char** argv) -> int {
	const auto graph = parse(argv[1]);
	auto remaining = graph | std::views::keys | std::ranges::to<std::vector>();
	auto current = std::vector<std::string>();
	auto max = std::vector<std::string>();
	solve(graph, current, remaining, max);
	std::ranges::sort(max);
	std::println("{}", max | std::ranges::views::join_with(',') | std::ranges::to<std::string>());
}
