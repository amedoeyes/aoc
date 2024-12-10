#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct hash {
	auto operator()(const std::pair<size_t, size_t>& x) const -> size_t {
		return x.first ^ (x.second << 1u);
	}
};

static auto parse(auto buffer) {
	const auto width = buffer.find('\n');
	const auto height = buffer.size() / (width + 1);
	const auto map = buffer																									 //
									 | std::views::filter([](char c) { return c != '\n'; })	 //
									 | std::views::transform([](char c) { return c - '0'; }) //
									 | std::ranges::to<std::vector<int64_t>>();
	return std::make_tuple(map, width, height);
}

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	const auto [map, w, h] = parse(buffer);

	auto graph = std::unordered_map<
		std::pair<size_t, size_t>,
		std::unordered_set<std::pair<size_t, size_t>, hash>,
		hash>();

	for (const auto y : std::views::iota(0ul, h)) {
		for (const auto x : std::views::iota(0ul, w)) {
			for (const auto dy : std::views::iota(-1l, 2l)) {
				for (const auto dx : std::views::iota(-1l, 2l)) {
					if ((dx == 0 && dy == 0) || (dx != 0 && dy != 0) || dx + x >= w || dy + y >= h) continue;
					graph[{x, y}].emplace(x + dx, y + dy);
				}
			}
		}
	}

	auto trailheads = graph //
										| std::views::transform([](const auto& pair) { return pair.first; })
										| std::views::filter([&map, &w](const auto& pair) {
												return map[(pair.second * w) + pair.first] == 0;
											});

	auto count = 0ul;
	for (const auto& pair : trailheads) {
		auto stack = std::stack<std::pair<size_t, size_t>>();
		stack.emplace(pair);
		while (!stack.empty()) {
			const auto [x, y] = stack.top();
			stack.pop();
			if (map[(y * w) + x] == 9) {
				++count;
				continue;
			}
			for (const auto& [nx, ny] : graph[{x, y}]) {
				if (static_cast<int64_t>(map[(ny * w) + nx]) - static_cast<int64_t>(map[(y * w) + x]) == 1)
					stack.emplace(nx, ny);
			}
		}
	}

	std::println("{}", count);
}
