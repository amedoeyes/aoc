#include <bits/stdc++.h>

struct hash {
	auto operator()(const std::pair<size_t, size_t>& x) const -> size_t {
		return x.first ^ (x.second << 1u);
	}
};

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();
	const auto w = buffer.find('\n') + 1;
	const auto h = buffer.size() / w;
	const auto get = [&buffer, w, h](size_t x, size_t y) {
		if (x >= w || y >= h) return '\0';
		return buffer[(y * w) + x];
	};

	auto sum = 0ul;
	auto queue = std::queue<std::pair<size_t, size_t>>();
	auto visited = std::unordered_set<std::pair<size_t, size_t>, hash>();
	for (const auto y : std::views::iota(0ul, h)) {
		for (const auto x : std::views::iota(0ul, w - 1)) {
			if (visited.contains({x, y})) continue;
			auto area = 1ul;
			auto sides = 0ul;
			queue.emplace(x, y);
			visited.emplace(x, y);
			while (!queue.empty()) {
				const auto [x, y] = queue.front();
				queue.pop();
				const auto ch = get(x, y);
				for (const auto dy : std::views::iota(-1, 2)) {
					for (const auto dx : std::views::iota(-1, 2)) {
						if (dx == 0 && dy == 0) continue;
						const auto nx = x + dx;
						const auto ny = y + dy;
						const auto nch = get(nx, ny);
						if (dx == 0 || dy == 0) {
							if (nch == ch && !visited.contains({nx, ny})) {
								++area;
								queue.emplace(nx, ny);
								visited.emplace(nx, ny);
							}
						} else {
							const auto hch = get(x + (nx - x), y);
							const auto vch = get(x, y + (ny - y));
							if ((nch != ch && hch == ch && vch == ch) || (hch != ch && vch != ch)) ++sides;
						}
					}
				}
			}
			sum += area * sides;
		}
	}

	std::println("{}", sum);
}
