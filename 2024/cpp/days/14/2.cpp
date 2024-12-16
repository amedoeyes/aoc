#include "vector2.hpp"
#include "vector_common.hpp"

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

	auto bots = parse(buffer);
	auto min_diff = std::numeric_limits<uint64_t>::max();
	auto min_sec = 0;
	for (const auto sec : std::views::iota(0, 10403)) {
		auto diff = 0ul;
		for (auto [a, b] : bots | std::views::adjacent<2>) {
			diff += length(abs(a.first - b.first));
		}
		if (diff < min_diff) {
			min_diff = diff;
			min_sec = sec;
		}
		for (auto& [p, v] : bots) {
			p.x = (p.x + v.x + size.x) % size.x;
			p.y = (p.y + v.y + size.y) % size.y;
		}
	}

	std::println("{}", min_sec);
}
