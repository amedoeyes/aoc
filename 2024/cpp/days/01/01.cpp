#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <print>
#include <ranges>
#include <vector>

auto main(int /*argc*/, char** argv) -> int {
	std::ifstream file(argv[1]);

	std::vector<int64_t> left;
	std::vector<int64_t> right;

	while (!file.eof()) {
		file >> left.emplace_back(0);
		file >> right.emplace_back(0);
	}

	std::ranges::sort(left);
	std::ranges::sort(right);

	int64_t total_difference = std::ranges::fold_left(
		std::views::zip_transform(
			[](int64_t l, int64_t r) {
				return std::abs(l - r);
			},
			left,
			right
		),
		0,
		std::plus<>()
	);

	std::println("{}", total_difference);

	return 0;
}
