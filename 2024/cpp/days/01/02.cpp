#include "utility.hpp"

#include <bits/ranges_algo.h>
#include <cstdint>
#include <fstream>
#include <print>
#include <regex>
#include <string>
#include <unordered_map>
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

	std::unordered_map<int32_t, int32_t> freq_map;
	for (const auto& id : right) {
		freq_map[id]++;
	}

	int32_t similarity_score = std::ranges::fold_left(left, 0, [&freq_map](int32_t acc, int32_t id) {
		return acc + (id * freq_map[id]);
	});

	std::println("{}", similarity_score);

	return 0;
}
