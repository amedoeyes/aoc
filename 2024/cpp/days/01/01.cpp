#include "utility.hpp"

#include <algorithm>
#include <bits/ranges_algo.h>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

auto main() -> int {
	std::ifstream file = readfile("./days/01/input.txt");

	std::vector<int32_t> left;
	std::vector<int32_t> right;

	for (std::string line; std::getline(file, line);) {
		const std::regex pattern("\\s{3}");
		std::sregex_token_iterator it(line.begin(), line.end(), pattern, -1);
		left.push_back(std::stoi(it->str()));
		right.push_back(std::stoi((++it)->str()));
	}

	std::ranges::sort(left);
	std::ranges::sort(right);

	int32_t total_difference = std::ranges::fold_left(
		std::views::zip(left, right),
		0,
		[](int32_t acc, std::tuple<int32_t, int32_t> pair) {
			auto [l, r] = pair;
			return acc + std::abs(l - r);
		}
	);

	std::println("{}", total_difference);

	return 0;
}
