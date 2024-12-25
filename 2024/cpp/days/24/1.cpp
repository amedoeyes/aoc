#include "file.hpp"

#include <bits/stdc++.h>

using namespace std::literals;

struct gate {
	char type;
	std::string in1;
	std::string in2;
	std::string out;
};

static auto parse(auto path) {
	auto parts = file(path).str() | std::views::split("\n\n"sv);
	auto it = parts.begin();
	auto wires = *it //
						 | std::views::split('\n') //
						 | std::views::transform([](auto line) {
								 auto parts = line | std::views::split(": "sv);
								 auto it = parts.begin();
								 auto wire = *it | std::ranges::to<std::string>();
								 auto value = std::string_view(*++it) == "1"sv;
								 return std::pair{wire, value};
							 })
						 | std::ranges::to<std::unordered_map>();
	auto gates = *++it //
						 | std::views::split('\n') //
						 | std::views::filter([](auto line) { return !line.empty(); })
						 | std::views::transform([](auto line) {
								 auto parts = line | std::views::split(" -> "sv);
								 auto it = parts.begin();
								 auto parts2 = *it | std::views::split(' ');
								 auto it2 = parts2.begin();
								 auto in1 = *it2 | std::ranges::to<std::string>();
								 auto type = std::string_view(*++it2)[0];
								 auto in2 = *++it2 | std::ranges::to<std::string>();
								 auto out = *++it | std::ranges::to<std::string>();
								 return gate{type, in1, in2, out};
							 })
						 | std::ranges::to<std::queue<gate>>();
	return std::tuple{wires, gates};
}

auto main(int /*argc*/, char** argv) -> int {
	auto [wires, gates] = parse(argv[1]);
	while (!gates.empty()) {
		const auto gate = gates.front();
		gates.pop();
		if (!wires.contains(gate.in1) || !wires.contains(gate.in2)) {
			gates.push(gate);
			continue;
		}
		switch (gate.type) {
			case 'A': wires[gate.out] = wires[gate.in1] && wires[gate.in2]; break;
			case 'O': wires[gate.out] = wires[gate.in1] || wires[gate.in2]; break;
			case 'X': wires[gate.out] = wires[gate.in1] ^ wires[gate.in2]; break;
			default: break;
		}
	}
	auto zwires = wires //
							| std::ranges::views::filter([](const auto& p) { return p.first[0] == 'z'; })
							| std::ranges::to<std::vector<std::pair<std::string, uint32_t>>>();
	std::ranges::sort(zwires, [](const auto& a, const auto& b) { return a.first > b.first; });
	const auto number =
		std::ranges::fold_left(zwires | std::ranges::views::values, 0ul, [](auto acc, auto b) {
			return (acc << 1u) | b;
		});
	std::println("{}", number);
	for (auto [k, v] : zwires) {
		std::println("{}: {}", k, v);
	}
}
