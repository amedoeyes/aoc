#include <algorithm>
#include <cstdint>
#include <fstream>
#include <print>
#include <ranges>
#include <unordered_map>
#include <vector>

auto main(int /*argc*/, char** argv) -> int {
	std::ifstream file(argv[1]);

	std::vector<int64_t> left;
	std::unordered_map<int64_t, int64_t> right_freq;

	while (!file.eof()) {
		file >> left.emplace_back(0);
		int64_t r = 0;
		file >> r;
		right_freq[r]++;
	}

	int64_t similarity_score = std::ranges::fold_left(
		std::views::transform(
			left,
			[&right_freq](int64_t l) {
				return l * right_freq[l];
			}
		),
		0,
		std::plus<>()
	);

	std::println("{}", similarity_score);

	return 0;
}
