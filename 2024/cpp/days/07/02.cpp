#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
#include <stack>
#include <string_view>
#include <utility>
#include <vector>

constexpr auto to_int = [](const std::ranges::view auto& str) {
	int64_t n = 0;
	std::from_chars(str.data(), str.data() + str.size(), n);
	return n;
};

constexpr auto is_empty = [](const std::ranges::view auto& str) { return !str.empty(); };

static auto parse(std::string_view buffer) -> std::ranges::view auto {
	return buffer													//
				 | std::views::split('\n')			//
				 | std::views::filter(is_empty) //
				 | std::views::transform([](const auto& line) {
						 auto parts = line | std::views::split(':');
						 auto it = parts.begin();
						 auto res = to_int(*it);
						 auto ops = *(++it) | std::views::split(' ') //
												| std::views::filter(is_empty)	 //
												| std::views::transform(to_int)	 //
												| std::ranges::to<std::vector<int64_t>>();
						 return std::make_pair(res, ops);
					 });
}

auto main(int /*argc*/, char** argv) -> int {
	auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	auto sum = std::ranges::fold_left(parse(buffer), 0ul, [](const auto& acc, const auto& eq) {
		const auto& [res, ops] = eq;
		auto stack = std::stack<std::pair<int64_t, size_t>>();
		stack.emplace(res, ops.size() - 1);
		while (!stack.empty()) {
			const auto [target, i] = stack.top();
			stack.pop();
			if (target == 0) return acc + res;
			if (i > ops.size() - 1) continue;
			const auto op = ops[i];
			const auto pot = static_cast<int64_t>(std::pow(10, std::floor(std::log10(op) + 1)));
			if (target % op == 0) stack.emplace(target / op, i - 1);
			if (target >= op) stack.emplace(target - op, i - 1);
			if (target >= op && ((target - op) % pot) == 0) stack.emplace(target / pot, i - 1);
		}
		return acc;
	});

	std::println("{}", sum);
}
