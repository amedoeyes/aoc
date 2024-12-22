#include "file.hpp"

#include <bits/stdc++.h>

static auto parse(auto path) {
	return file(path).str() //
			 | std::views::split('\n') //
			 | std::views::filter([](auto line) { return !line.empty(); })
			 | std::views::transform([](auto line) {
					 int64_t n = 0;
					 std::from_chars(line.data(), line.data() + line.size(), n);
					 return n;
				 })
			 | std::ranges::to<std::vector<uint64_t>>();
}

auto main(int /*argc*/, char** argv) -> int {
	const auto secrets = parse(argv[1]);
	const auto new_secrets = secrets | std::views::transform([](auto secret) {
														 for (auto _ : std::views::iota(0, 2000)) {
															 secret = ((secret << 6u) ^ secret) & 0xFFFFFFu;
															 secret = ((secret >> 5u) ^ secret) & 0xFFFFFFu;
															 secret = ((secret << 11u) ^ secret) & 0xFFFFFFu;
														 }
														 return secret;
													 });
	const auto sum = std::ranges::fold_left(new_secrets, 0ul, std::plus<>());
	std::println("{}", sum);
}
