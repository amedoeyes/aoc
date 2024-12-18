#include <bits/stdc++.h>
#include <cstdint>
#include <print>
#include <ranges>
#include <sys/types.h>
#include <utility>

static auto parse(auto path) {
	const auto buffer = (std::ostringstream() << std::ifstream(path).rdbuf()).str();
	auto parts = buffer | std::views::split(std::string_view("\n\n"));
	const auto regs =
		*parts.begin() //
		| std::views::split('\n') //
		| std::ranges::views::transform([](const auto part) {
				auto str =
					std::string_view(part | std::views::drop_while([](const auto ch) { return ch != ':'; }));
				auto n = 0l;
				std::from_chars(str.data() + 2, str.data() + str.size(), n);
				return n;
			})
		| std::ranges::to<std::vector<uint64_t>>();
	const auto ins = *(++parts.begin())
								 | std::views::drop_while([](const auto ch) { return ch != ':'; })
								 | std::views::drop(2) //
								 | std::views::split(',') //
								 | std::views::transform([](const auto part) {
										 auto n = 0l;
										 std::from_chars(part.data(), part.data() + part.size(), n);
										 return n;
									 })
								 | std::ranges::to<std::vector<uint64_t>>();
	return std::tuple(regs, ins);
}

auto main(int /*argc*/, char** argv) -> int {
	auto [regs, ins] = parse(argv[1]);
	const auto combo = [&regs](const auto n) { return n < 4 ? n : regs[n - 4]; };
	auto ra = 0ul;
	for (auto i : std::views::iota(0ul, ins.size())) {
		ra <<= 3u;
		while (true) {
			auto out = std::vector<uint64_t>();
			auto ip = 0u;
			regs = {ra, 0, 0};
			while (ip < ins.size()) {
				const auto in = ins[ip++];
				const auto op = ins[ip++];
				switch (in) {
					case 0: regs[0] >>= combo(op); break;
					case 1: regs[1] ^= op; break;
					case 2: regs[1] = combo(op) & 7u; break;
					case 3: ip = regs[0] > 0 ? op : ip; break;
					case 4: regs[1] ^= regs[2]; break;
					case 5: out.push_back(combo(op) & 7u); break;
					case 6: regs[1] = regs[0] >> combo(op); break;
					case 7: regs[2] = regs[0] >> combo(op); break;
					default: std::unreachable();
				}
			}
			if (std::ranges::equal(
						out | std::views::reverse, //
						ins | std::views::reverse | std::views::take(i + 1)
					))
				break;
			++ra;
		}
	}
	std::println("{}", ra);
}
