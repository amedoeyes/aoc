#include "vector.hpp"
#include "vector2.hpp"

#include <bits/stdc++.h>

struct hash {
	template <typename T>
	auto operator()(const vector<2, T>& v) const -> size_t {
		return v.x ^ (v.y << 1u);
	}
};

static auto parse(auto path) {
	const auto buffer = (std::ostringstream() << std::ifstream(path).rdbuf()).str();
	auto parts = buffer | std::views::split(std::string_view("\n\n"));
	const auto map = *std::ranges::begin(parts);
	const auto width = std::ranges::distance(map | std::views::split('\n')) + 1;
	const auto height = static_cast<int64_t>(map.size() / (width - 1));
	auto bot = vector<2, int64_t>();
	auto walls = std::unordered_set<vector<2, int64_t>, hash>();
	auto boxes = std::unordered_set<vector<2, int64_t>, hash>();
	for (const auto y : std::views::iota(0l, height)) {
		for (const auto x : std::views::iota(0l, width)) {
			const auto ch = map.data()[(y * width) + x];
			switch (ch) {
				case '#': walls.emplace(x, y); break;
				case 'O': boxes.emplace(x, y); break;
				case '@': bot = {x, y}; break;
				default: break;
			}
		}
	}
	const auto moves = *std::ranges::next(std::ranges::begin(parts)) //
									 | std::views::filter([](auto ch) { return ch != '\n'; }) //
									 | std::views::transform([](auto move) {
											 switch (move) {
												 case '^': return vector(0l, -1l); break;
												 case '>': return vector(1l, 0l); break;
												 case 'v': return vector(0l, 1l); break;
												 case '<': return vector(-1l, 0l); break;
												 default: std::unreachable();
											 }
										 })
									 | std::ranges::to<std::vector<vector<2, int64_t>>>();
	return std::tuple(bot, walls, boxes, moves);
}

auto main(int /*argc*/, char** argv) -> int {
	auto [bot, walls, boxes, moves] = parse(argv[1]);
	for (const auto& m : moves) {
		auto next = bot + m;
		auto temp = std::vector<vector<2, int64_t>>();
		while (boxes.contains(next)) {
			temp.emplace_back(next);
			boxes.erase(next);
			next += m;
		}
		if (walls.contains(next)) {
			for (const auto& b : temp) boxes.emplace(b);
			continue;
		}
		for (const auto& b : temp) boxes.emplace(b + m);
		bot += m;
	}
	const auto sum = std::ranges::fold_left(boxes, 0ul, [](auto acc, const auto& b) {
		return acc + (b.y * 100 + b.x);
	});
	std::println("{}", sum);
}
