#include "vector2.hpp"

#include <bits/stdc++.h>

static auto parse(std::string_view buffer) {
	return buffer //
			 | std::views::split('\n') //
			 | std::views::filter([](auto line) { return !line.empty(); })
			 | std::views::transform([](auto line) {
					 auto parts = line //
											| std::views::split(' ') //
											| std::views::transform([](auto part) {
													return part //
															 | std::views::drop(2) //
															 | std::views::split(',') //
															 | std::views::transform([](auto part) {
																	 auto n = 0l;
																	 std::from_chars(part.data(), part.data() + part.size(), n);
																	 return n;
																 });
												});
					 auto p = *parts.begin();
					 auto v = *(++parts.begin());
					 return std::pair(
						 vector<2, int64_t>(*p.begin(), *(++p.begin())),
						 vector<2, int64_t>(*v.begin(), *(++v.begin()))
					 );
				 })
			 | std::ranges::to<std::vector<std::pair<vector<2, int64_t>, vector<2, int64_t>>>>();
}

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();
	const auto size = vector<2, int64_t>(101, 103);
	const auto half_size = size / 2l;

	auto bots = parse(buffer);
	auto qs = std::array<int64_t, 4>();
	for (auto& [p, v] : bots) {
		for (auto _ : std::views::iota(0, 100)) {
			p.x = (p.x + v.x + size.x) % size.x;
			p.y = (p.y + v.y + size.y) % size.y;
		}
		if (p.x < half_size.x && p.y < half_size.y) ++qs[0];
		if (p.x > half_size.x && p.y < half_size.y) ++qs[1];
		if (p.x < half_size.x && p.y > half_size.y) ++qs[2];
		if (p.x > half_size.x && p.y > half_size.y) ++qs[3];
	}

	const auto factor = std::ranges::fold_left(qs, 1ul, std::multiplies<>());

	std::println("{}", factor);
}
