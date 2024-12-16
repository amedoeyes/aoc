#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <sstream>
#include <stack>

struct hash {
	auto operator()(const std::pair<size_t, size_t>& x) const -> size_t {
		return x.first ^ (x.second << 1u);
	}
};

constexpr auto directions =
	std::array<std::pair<int64_t, int64_t>, 4>({{0, 1}, {1, 0}, {0, -1}, {-1, 0}});

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();
	const auto w = buffer.find('\n') + 1;
	const auto h = buffer.size() / w;

	auto count = 0ul;
	auto stack = std::stack<std::pair<size_t, size_t>>();
	for (auto y = 0ul; y < h; ++y) {
		for (auto x = 0ul; x < w; ++x) {
			if (buffer[(y * w) + x] != '0') continue;
			stack.emplace(x, y);
			while (!stack.empty()) {
				const auto [x, y] = stack.top();
				stack.pop();
				for (const auto& [dx, dy] : directions) {
					const auto nx = x + dx;
					const auto ny = y + dy;
					if (nx < w && ny < h && buffer[(ny * w) + nx] - buffer[(y * w) + x] == 1) {
						if (buffer[(ny * w) + nx] == '9') ++count;
						else stack.emplace(nx, ny);
					}
				}
			}
		}
	}

	std::println("{}", count);
}
