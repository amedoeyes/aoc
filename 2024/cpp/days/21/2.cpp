#include "file.hpp"

#include <bits/stdc++.h>

static auto parse(auto path) {
	return file(path).str() //
			 | std::views::split('\n') //
			 | std::views::filter([](auto line) { return !line.empty(); })
			 | std::ranges::to<std::vector<std::string>>();
}

// clang-format off
const auto numpad = std::unordered_map<char, std::unordered_map<char, std::vector<std::string>>>{
	{'A', {{'A', {""}},             {'0', {"<"}},            {'1', {"^<<"}},          {'2', {"<^", "^<"}},   {'3', {"^"}},            {'4', {"^^<<"}},       {'5', {"<^^", "^^<"}}, {'6', {"^^"}},         {'7', {"^^^<<"}},        {'8', {"<^^^", "^^^<"}}, {'9', {"^^^"}}}},
	{'0', {{'A', {">"}},            {'0', {""}},             {'1', {"^<"}},           {'2', {"^"}},          {'3', {">^", "^>"}},     {'4', {"^^<"}},        {'5', {"^^"}},         {'6', {">^^", "^^>"}}, {'7', {"^^^<"}},         {'8', {"^^^"}},          {'9', {">^^^", "^^^>"}}}},
	{'1', {{'A', {">>v"}},          {'0', {">v"}},           {'1', {""}},             {'2', {">"}},          {'3', {">>"}},           {'4', {"^"}},          {'5', {">^", "^>"}},   {'6', {">>^", "^>>"}}, {'7', {"^^"}},           {'8', {">^^", "^^>"}},   {'9', {">>^^", "^^>>"}}}},
	{'2', {{'A', {"v>", ">v"}},     {'0', {"v"}},            {'1', {"<"}},            {'2', {""}},           {'3', {">"}},            {'4', {"<^", "^<"}},   {'5', {"^"}},          {'6', {">^", "^>"}},   {'7', {"<^^", "^^<"}},   {'8', {"^^"}},           {'9', {">^^", "^^>"}}}},
	{'3', {{'A', {"v"}},            {'0', {"<v", "v<"}},     {'1', {"<<"}},           {'2', {"<"}},          {'3', {""}},             {'4', {"<<^", "^<<"}}, {'5', {"<^", "^<"}},   {'6', {"^"}},          {'7', {"<<^^", "^^<<"}}, {'8', {"<^^", "^^<"}},   {'9', {"^^"}}}},
	{'4', {{'A', {">>vv"}},         {'0', {">vv"}},          {'1', {"v"}},            {'2', {"v>", ">v"}},   {'3', {"v>>", ">>v"}},   {'4', {""}},           {'5', {">"}},          {'6', {">>"}},         {'7', {"^"}},            {'8', {">^", "^<"}},     {'9', {">>^", "^>>"}}}},
	{'5', {{'A', {"vv>", ">vv"}},   {'0', {"vv"}},           {'1', {"<v", "v<"}},     {'2', {"v"}},          {'3', {"v>", ">v"}},     {'4', {"<"}},          {'5', {""}},           {'6', {">"}},          {'7', {"<^", "^<"}},     {'8', {"^"}},            {'9', {">^", "^>"}}}},
	{'6', {{'A', {"vv"}},           {'0', {"<vv", "vv<"}},   {'1', {"<<v", "v<<"}},   {'2', {"<v", "v<"}},   {'3', {"v"}},            {'4', {"<<"}},         {'5', {"<"}},          {'6', {""}},           {'7', {"<<^", "^<<"}},   {'8', {"<^", "^<"}},     {'9', {"^"}}}},
	{'7', {{'A', {">>vvv"}},        {'0', {">vvv"}},         {'1', {"vv"}},           {'2', {"vv>", ">vv"}}, {'3', {"vv>>", ">>vv"}}, {'4', {"v"}},          {'5', {"v>" ,">v"}},   {'6', {"v>>", ">>v"}}, {'7', {""}},             {'8', {">"}},            {'9', {">>"}}}},
	{'8', {{'A', {"vvv>" ,">vvv"}}, {'0', {"vvv"}},          {'1', {"<vv", "vv<"}},   {'2', {"vv"}},         {'3', {"vv>", ">vv"}},   {'4', {"<v", "v<"}},   {'5', {"v"}},          {'6', {"v>" ,">v"}},   {'7', {"<"}},            {'8', {""}},             {'9', {">"}}}},
	{'9', {{'A', {"vvv"}},          {'0', {"<vvv", "vvv<"}}, {'1', {"<<vv", "vv<<"}}, {'2', {"<vv", "vv<"}}, {'3', {"vv"}},           {'4', {"<<v", "v<<"}}, {'5', {"<v", "v<"}},   {'6', {"v"}},          {'7', {"<<"}},           {'8', {"<"}},            {'9', {""}}}},
};

const auto dirpad = std::unordered_map<char, std::unordered_map<char, std::vector<std::string>>>{
	{'A', {{'A', {""}},         {'^', {"<"}},        {'>', {"v"}},        {'v', {"<v", "v<"}}, {'<', {"v<<"}}}},
	{'^', {{'A', {">"}},        {'^', {""}},         {'>', {">v", "v>"}}, {'v', {"v"}},        {'<', {"v<"}}}},
	{'>', {{'A', {"^"}},        {'^', {"<^", "^<"}}, {'>', {""}},         {'v', {"<"}},        {'<', {"<<"}}}},
	{'v', {{'A', {">^", "^>"}}, {'^', {"^"}},        {'>', {">"}},        {'v', {""}},         {'<', {"<"}}}},
	{'<', {{'A', {">>^"}},      {'^', {">^"}},       {'>', {">>"}},       {'v', {">"}},        {'<', {""}}}},
};
// clang-format on

struct hash {
	auto operator()(const std::tuple<char, char, int64_t>& key) const -> size_t {
		auto [c1, c2, num] = key;
		return std::hash<char>{}(c1) ^ (std::hash<char>{}(c2) << 8u)
				 ^ (std::hash<int64_t>{}(num) << 16u);
	}
};

static auto cache = std::unordered_map<std::tuple<char, char, int64_t>, uint64_t, hash>();

static auto solve(char from, char to, int64_t level = 25) -> uint64_t {
	if (cache.contains({from, to, level})) return cache[{from, to, level}];
	if (level == 25) {
		auto size = std::numeric_limits<uint64_t>::max();
		for (const auto& path : numpad.at(from).at(to)) {
			auto psize = 0ul;
			for (const auto [from, to] : ('A' + path + 'A') | std::views::adjacent<2>) {
				if (cache.contains({from, to, level - 1})) psize += cache[{from, to, level - 1}];
				else psize += solve(from, to, level - 1);
			}
			size = std::min(size, psize);
		}
		return cache[{from, to, level}] = size;
	}
	if (level == 0) return cache[{from, to, level}] = dirpad.at(from).at(to).at(0).size() + 1;
	auto size = std::numeric_limits<uint64_t>::max();
	for (const auto& path : dirpad.at(from).at(to)) {
		auto psize = 0ul;
		for (const auto [from, to] : ('A' + path + 'A') | std::views::adjacent<2>) {
			if (cache.contains({from, to, level - 1})) psize += cache[{from, to, level - 1}];
			else psize += solve(from, to, level - 1);
		}
		size = std::min(size, psize);
	}
	return cache[{from, to, level}] = size;
}

auto main(int /*argc*/, char** argv) -> int {
	const auto codes = parse(argv[1]);
	auto sum = 0ul;
	for (const auto& code : codes) {
		auto size = 0ul;
		for (const auto [from, to] : ('A' + code) | std::views::adjacent<2>) {
			size += solve(from, to);
		}
		auto n = 0ul;
		std::from_chars(code.data(), code.data() + code.size(), n);
		sum += n * size;
	}
	std::println("{}", sum);
}
