#include <cctype>
#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <string>

auto parse_number(std::string_view& sv) -> std::optional<int64_t> {
	int64_t value = 0;
	auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
	if (ec == std::errc{}) {
		sv.remove_prefix(ptr - sv.data());
		return value;
	}
	return std::nullopt;
}

auto main(int /*argc*/, char** argv) -> int {
	std::ifstream file(argv[1]);

	int64_t sum = 0;
	bool enabled = true;
	for (std::string line; std::getline(file, line);) {
		std::string_view sv(line);
		while (!sv.empty()) {
			if (sv.starts_with("mul(") && enabled) {
				sv.remove_prefix(4);
				const std::optional<int64_t> a = parse_number(sv);
				if (!a || sv.empty() || sv.front() != ',') {
					continue;
				}
				sv.remove_prefix(1);
				const std::optional<int64_t> b = parse_number(sv);
				if (!b || sv.empty() || sv.front() != ')') {
					continue;
				}
				sv.remove_prefix(1);
				sum += *a * *b;
			} else if (sv.starts_with("do()")) {
				enabled = true;
				sv.remove_prefix(4);
			} else if (sv.starts_with("don't()")) {
				enabled = false;
				sv.remove_prefix(7);
			} else {
				sv.remove_prefix(1);
			}
		}
	}

	std::println("{}", sum);

	return 0;
}
