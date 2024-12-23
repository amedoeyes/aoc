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
									 | std::ranges::to<std::vector<std::pair<std::string, std::string>>>();
	auto graph = std::unordered_map<std::string, std::unordered_set<std::string>>();
	for (const auto& [from, to] : pairs) {
		graph[from].emplace(to);
		graph[to].emplace(from);
	}
	return graph;
}

struct hash {
	auto operator()(const std::array<std::string, 3>& array) const -> size_t {
		const auto [a, b, c] = array;
		return std::hash<std::string>{}(a) + std::hash<std::string>{}(b) + std::hash<std::string>{}(c);
	}
};

auto main(int /*argc*/, char** argv) -> int {
	const auto graph = parse(argv[1]);
	auto triplets = std::unordered_set<std::array<std::string, 3>, hash>();
	for (const auto& node : graph | std::views::keys) {
		for (const auto& neighbor : graph.at(node)) {
			for (const auto& neighbor2 : graph.at(neighbor)) {
				if (graph.at(neighbor2).contains(node)) {
					auto array = std::array{node, neighbor, neighbor2};
					std::ranges::sort(array);
					triplets.emplace(array);
				}
			}
		}
	}
	const auto count = std::ranges::count_if(triplets, [](const auto& triplet) {
		return std::ranges::any_of(triplet, [](const auto& con) { return con.starts_with('t'); });
	});
	std::println("{}", count);
}
