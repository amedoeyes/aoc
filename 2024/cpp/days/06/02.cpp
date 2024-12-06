#include <array>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

struct hash {
	auto operator()(const std::pair<size_t, size_t>& x) const -> size_t {
		return x.first ^ (x.second << 1u);
	}
};

constexpr auto directions =
	std::array<std::pair<size_t, size_t>, 4>({{0, -1}, {1, 0}, {0, 1}, {-1, 0}});

auto main(int /*argc*/, char** argv) -> int {
	auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	auto w = buffer.find('\n') + 1;
	auto h = buffer.size() / (w);
	auto pos = buffer.find('^');

	auto x = pos % (w);
	auto y = pos / (w);
	auto dir = 0ul;
	auto visited = std::unordered_set<std::pair<size_t, size_t>, hash>();
	while (x < w && y < h) {
		const auto [dx, dy] = directions[dir];
		const auto x2 = x + dx;
		const auto y2 = y + dy;
		if (x2 < w && y2 < h && buffer[(y2 * w) + x2] == '#') {
			dir = (dir + 1) % directions.size();
			continue;
		}
		visited.emplace(x, y);
		x = x2;
		y = y2;
	}

	auto count = 0;
	for (const auto& [ox, oy] : visited) {
		auto x = pos % w;
		auto y = pos / w;
		auto dir = 0ul;
		auto obstacles = std::unordered_map<std::pair<size_t, size_t>, size_t, hash>();
		while (x < w && y < h) {
			const auto [dx, dy] = directions[dir];
			const auto x2 = x + dx;
			const auto y2 = y + dy;
			if ((x2 < w && y2 < h && buffer[(y2 * w) + x2] == '#') || (x2 == ox && y2 == oy)) {
				auto [it, success] = obstacles.emplace(std::make_pair(x2, y2), dir);
				if (!success && it->second == dir) {
					++count;
					break;
				}
				dir = (dir + 1) % directions.size();
				continue;
			}
			x = x2;
			y = y2;
		}
	}

	std::println("{}", count);
}
