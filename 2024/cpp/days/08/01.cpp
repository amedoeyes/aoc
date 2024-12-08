#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>

struct hash {
	auto operator()(const std::pair<size_t, size_t>& x) const -> size_t {
		return x.first ^ (x.second << 1u);
	}
};

auto main(int /*argc*/, char** argv) -> int {
	auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	const auto w = buffer.find('\n') + 1;
	const auto h = buffer.size() / w;

	auto antinodes = std::unordered_set<std::pair<size_t, size_t>, hash>();
	for (const auto y : std::views::iota(0ul, h)) {
		for (const auto x : std::views::iota(0ul, w)) {
			const auto ch = buffer[(y * w) + x];
			if (ch == '.' || ch == '\n') continue;
			auto pos = buffer.find(ch, ((y * w) + x) + 1);
			while (pos != std::string::npos) {
				const auto x2 = (pos % w);
				const auto y2 = (pos / w);
				const auto dx = static_cast<int64_t>(x - x2);
				const auto dy = static_cast<int64_t>(y - y2);
				const auto y3 = y + dy;
				const auto x3 = x + dx;
				if (y3 < h && x3 < w - 1) antinodes.emplace(x3, y3);
				const auto y4 = y2 - dy;
				const auto x4 = x2 - dx;
				if (y4 < h && x4 < w - 1) antinodes.emplace(x4, y4);
				pos = buffer.find(ch, ((y2 * w) + x2) + 1);
			}
		}
	}

	std::println("{}", antinodes.size());
}
