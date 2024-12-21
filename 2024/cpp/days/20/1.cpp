#include "file.hpp"
#include "grid.hpp"
#include "vector.hpp"
#include "vector2.hpp"

#include <bits/stdc++.h>
#include <print>

struct vector_hash {
	template <typename T>
	auto operator()(const vector<2, T>& v) const -> size_t {
		return v.x ^ (v.y << 1);
	}
};

struct pair_hash {
	template <typename T>
	auto operator()(const std::pair<vector<2, T>, vector<2, T>>& p) const -> size_t {
		return vector_hash{}(p.first) ^ (vector_hash{}(p.second) << 1);
	}
};

struct cmp {
	auto operator()(const auto& a, const auto& b) const -> bool {
		return std::get<1>(a) > std::get<1>(b);
	}
};

static auto parse(auto path) {
	const auto buffer = file(path).str();
	const auto grid = create_grid(buffer);
	const auto start = find(grid, 'S');
	const auto end = find(grid, 'E');
	auto nodes = create_nodes(grid)
						 | std::views::filter([&](const auto& n) { return get(grid, n) != '#'; })
						 | std::ranges::to<std::unordered_set<vector<2, int64_t>, vector_hash>>();
	return std::tuple(nodes, start, end);
}

static auto manhattan_dist(const vector<2, int64_t>& a, const vector<2, int64_t>& b) -> int64_t {
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
};

auto main(int /*argc*/, char** argv) -> int {
	const auto [nodes, start, end] = parse(argv[1]);
	auto queue = std::queue<std::tuple<vector<2, int64_t>, int64_t>>();
	queue.emplace(start, 0);
	auto path = std::vector<vector<2, int64_t>>();
	auto visited = std::unordered_set<vector<2, int64_t>, vector_hash>();
	while (!queue.empty()) {
		const auto [pos, pico] = queue.front();
		queue.pop();
		if (visited.contains(pos)) continue;
		visited.emplace(pos);
		path.emplace_back(pos);
		if (pos == end) break;
		for (const auto& npos : get_neighbors(pos, cardinal_directions)) {
			if (nodes.contains(npos)) queue.emplace(npos, pico + 1);
		}
	}
	auto count = 0l;
	for (auto i = 0ul; i < path.size(); ++i) {
		for (auto j = i + 1; j < path.size(); ++j) {
			const auto dist = manhattan_dist(path[i], path[j]);
			if (dist <= 2 && j - i - dist >= 100) ++count;
		}
	}
	std::println("{}", count);
}
