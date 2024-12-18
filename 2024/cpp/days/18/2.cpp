#include "grid.hpp"
#include "to_string.hpp"
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
	auto buffer = (std::ostringstream() << std::ifstream(path).rdbuf()).str();
	return buffer //
			 | std::views::split('\n') //
			 | std::views::filter([](auto line) { return !line.empty(); })//
			 | std::views::transform([](auto line) {
					 auto parts = line | std::views::split(',');
					 auto it = parts.begin();
					 auto x = 0l;
					 auto y = 0l;
					 std::from_chars((*it).data(), (*it).data() + (*it).size(), x);
					 ++it;
					 std::from_chars((*it).data(), (*it).data() + (*it).size(), y);
					 return vector(x, y);
				 })
			 | std::ranges::to<std::vector<vector<2, int64_t>>>();
}

auto main(int /*argc*/, char** argv) -> int {
	const auto bytes = parse(argv[1]);
	const auto size = vector<2, int64_t>(71);
	auto low = 0ul;
	auto high = bytes.size();
	while (low <= high) {
		const auto mid = (low + high) / 2;
		const auto bytes_set = bytes //
												 | std::views::take(mid)
												 | std::ranges::to<std::unordered_set<vector<2, int64_t>, hash>>();
		auto queue = std::queue<std::pair<vector<2, int64_t>, int64_t>>();
		auto visited = std::unordered_set<vector<2, int64_t>, hash>();
		queue.emplace(vector(0l, 0l), 0);
		visited.emplace(0, 0);
		bool clear = false;
		while (!queue.empty()) {
			const auto [pos, step] = queue.front();
			queue.pop();
			if (pos == size - 1l) {
				clear = true;
				break;
			}
			for (const auto npos : get_neighbors(pos, cardinal_directions)) {
				if (in_bounds(npos, size) && !bytes_set.contains(npos) && !visited.contains(npos)) {
					queue.emplace(npos, step + 1);
					visited.emplace(npos);
				}
			}
		}
		if (clear) low = mid + 1;
		else high = mid - 1;
	}
	std::println("{}", to_string(bytes[high]));
}
