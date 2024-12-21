#ifndef GRID_HPP
#define GRID_HPP

#include "vector2.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <string_view>
#include <vector>

constexpr auto cardinal_directions = std::array<vector<2, int64_t>, 4>({
	{0, 1},
	{1, 0},
	{0, -1},
	{-1, 0},
});

constexpr auto diagonal_directions = std::array<vector<2, int64_t>, 4>({
	{1, 1},
	{1, -1},
	{-1, -1},
	{-1, 1},
});

constexpr auto directions = std::array<vector<2, int64_t>, 8>({
	{0, 1},
	{1, 1},
	{1, 0},
	{1, -1},
	{0, -1},
	{-1, -1},
	{-1, 0},
	{-1, 1},
});

struct grid {
	std::string data;
	vector<2, int64_t> size;
};

constexpr auto create_grid(std::string_view buffer) -> grid {
	const auto grid = buffer | std::views::filter([](auto ch) { return ch != '\n'; })
									| std::ranges::to<std::string>();
	const auto width = static_cast<int64_t>(buffer.find('\n'));
	const auto height = static_cast<int64_t>(buffer.size() / (width + 1));
	return {.data = grid, .size = {width, height}};
}

constexpr auto create_nodes(const grid& grid) -> std::vector<vector<2, int64_t>> {
	return std::views::iota(0l, grid.size.x) //
			 | std::views::transform([&](auto x) {
					 return std::views::iota(0l, grid.size.y)
								| std::views::transform([x](auto y) { return vector(x, y); });
				 })
			 | std::views::join //
			 | std::ranges::to<std::vector<vector<2, int64_t>>>();
}

constexpr auto to_index(const vector<2, int64_t>& pos, int64_t width) -> int64_t {
	return (pos.y * width) + pos.x;
}

constexpr auto from_index(int64_t index, int64_t width) -> vector<2, int64_t> {
	return {index % width, index / width};
}

constexpr auto in_bounds(const vector<2, int64_t>& pos, const vector<2, int64_t>& size) -> bool {
	return pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y;
}

constexpr auto get(const grid& grid, const vector<2, int64_t>& pos) -> char {
	if (!in_bounds(pos, grid.size)) return '\0';
	return grid.data[to_index(pos, grid.size.x)];
}

constexpr auto find(const grid& grid, char ch) -> vector<2, int64_t> {
	return from_index(static_cast<int64_t>(grid.data.find(ch)), grid.size.x);
}

template <size_t N>
constexpr auto get_neighbors(
	const vector<2, int64_t>& pos, const std::array<vector<2, int64_t>, N>& directions
) -> std::array<vector<2, int64_t>, N> {
	auto neighbors = std::array<vector<2, int64_t>, N>();
	for (auto i = 0ul; i < N; ++i) neighbors[i] = pos + directions[i];
	return neighbors;
}

#endif // !GRID_HPP
