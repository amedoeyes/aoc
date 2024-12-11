#include <bits/stdc++.h>

static auto parse(std::string_view buffer) {
	return buffer										//
				 | std::views::split(' ') //
				 | std::views::transform([](auto stone) {
						 auto n = 0l;
						 std::from_chars(stone.data(), stone.data() + stone.size(), n);
						 return n;
					 })
				 | std::ranges::to<std::vector<int64_t>>();
}

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	auto current = std::unordered_map<int64_t, int64_t>();
	auto next = std::unordered_map<int64_t, int64_t>();

	for (const auto stone : parse(buffer)) ++current[stone];

	for (auto _ : std::views::iota(0, 75)) {
		next.clear();
		for (const auto [stone, count] : current) {
			if (stone == 0) {
				next[1] += count;
				continue;
			}
			const auto digits = static_cast<int64_t>(std::log10(stone) + 1);
			if (digits % 2 == 0) {
				const auto pot = static_cast<int64_t>(std::pow(10, digits / 2));
				const auto left = stone / pot;
				const auto right = stone % pot;
				next[left] += count;
				next[right] += count;
				continue;
			}
			next[stone * 2024] += count;
		}
		std::swap(current, next);
	}

	const auto sum = std::ranges::fold_left(current | std::views::values, 0ul, std::plus<>());

	std::println("{}", sum);
}
