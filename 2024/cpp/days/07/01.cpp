#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <print>
#include <ranges>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <utility>
#include <vector>

constexpr auto to_int = [](const std::ranges::view auto& str) {
	int64_t n = 0;
	std::from_chars(str.data(), str.data() + str.size(), n);
	return n;
};

static auto parse(std::string_view buffer) //
	-> std::vector<std::pair<int64_t, std::vector<int64_t>>> {
	return buffer																																//
				 | std::views::split('\n')																						//
				 | std::views::filter([](const auto& line) { return !line.empty(); }) //
				 | std::views::transform([](const auto& line) {
						 auto parts = line | std::views::split(':');
						 auto it = parts.begin();
						 auto result = to_int(*it);
						 auto operands =
							 *(++it) | std::views::split(' ')																						//
							 | std::views::filter([](const auto& operand) { return !operand.empty(); }) //
							 | std::views::transform(to_int)																						//
							 | std::ranges::to<std::vector<int64_t>>();
						 return std::make_pair(result, operands);
					 }) //
				 | std::ranges::to<std::vector<std::pair<int64_t, std::vector<int64_t>>>>();
}

const auto operations = std::array<std::function<int64_t(int64_t, int64_t)>, 2>({
	std::plus<>(),
	std::multiplies<>(),
});

auto main(int /*argc*/, char** argv) -> int {
	auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	auto equations = parse(buffer);
	auto sum = std::ranges::fold_left(equations, 0ul, [](const auto& acc, const auto& eq) {
		const auto& [result, operands] = eq;
		for (auto i : std::views::iota(0, std::pow(operations.size(), operands.size() - 1))) {
			auto res = std::ranges::fold_left_first(operands, [&i](const auto& a, const auto& b) {
				auto res = operations[i % operations.size()](a, b);
				i /= operations.size();
				return res;
			});
			if (res == result) return acc + *res;
		}
		return acc;
	});

	std::println("{}", sum);
}
