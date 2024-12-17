#include "vector.hpp"
#include "vector2.hpp"

#include <bits/stdc++.h>

struct vector_hash {
	template <typename T>
	auto operator()(const vector<2, T>& v) const -> size_t {
		return v.x ^ (v.y << 1);
	}
};

struct pair_hash {
	template <typename T>
	auto operator()(const std::pair<vector<2, T>, int64_t>& p) const -> size_t {
		return vector_hash{}(p.first) ^ (p.second << 1);
	}
};

struct cmp {
	auto operator()(const auto& a, const auto& b) const -> bool {
		return std::get<1>(a) > std::get<1>(b);
	}
};

static auto parse(auto path) {
	const auto buffer = (std::ostringstream() << std::ifstream(path).rdbuf()).str();
	const auto grid = buffer //
									| std::views::filter([](auto ch) { return ch != '\n'; })
									| std::ranges::to<std::string>();
	const auto width = buffer.find('\n');
	const auto height = grid.size() / width;
	const auto start = grid.find('S');
	const auto end = grid.find('E');
	auto nodes = std::views::iota(0ul, width) //
						 | std::views::transform([height](int64_t x) {
								 return std::views::iota(0ul, height)
											| std::views::transform([x](int64_t y) { return vector(x, y); });
							 })
						 | std::views::join //
						 | std::views::filter([&grid, width](const auto& v) {
								 return grid[(v.y * width) + v.x] != '#';
							 });
	auto nodes_set = std::unordered_set<vector<2, int64_t>, vector_hash>();
	for (const auto& n : nodes) nodes_set.emplace(n);
	return std::tuple(
		nodes_set,
		vector<2, int64_t>(start % width, start / width),
		vector<2, int64_t>(end % width, end / width)
	);
}

constexpr auto directions = std::array<vector<2, int64_t>, 4>({{0, -1}, {1, 0}, {0, 1}, {-1, 0}});

auto main(int /*argc*/, char** argv) -> int {
	const auto [nodes, start, end] = parse(argv[1]);
	auto score = std::unordered_map<std::pair<vector<2, int64_t>, int64_t>, int64_t, pair_hash>();
	auto pqueue = std::priority_queue<
		std::tuple<vector<2, int64_t>, int64_t, int64_t>,
		std::vector<std::tuple<vector<2, int64_t>, int64_t, int64_t>>,
		cmp>();
	score[{start, 1}] = 0;
	pqueue.emplace(start, 0, 1);
	while (!pqueue.empty()) {
		const auto [n, s, d] = pqueue.top();
		pqueue.pop();
		if (n == end) {
			std::println("{}", s);
			break;
		}
		auto nn = n + directions[d];
		auto ns = s + 1;
		if (nodes.contains(nn) && (!score.contains({nn, d}) || ns < score[{nn, d}])) {
			score[{nn, d}] = ns;
			pqueue.emplace(nn, ns, d);
		}
		ns = s + 1000;
		for (const auto nd : std::array<int64_t, 2>({(d + 1) % 4, (d - 1 + 4) % 4})) {
			if (!score.contains({n, nd}) || ns < score[{n, nd}]) {
				score[{n, nd}] = ns;
				pqueue.emplace(n, ns, nd);
			}
		}
	}
}
