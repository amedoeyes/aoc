#ifndef GRID_HPP
#define GRID_HPP

#include "vector2.hpp"

#include <array>
#include <cstdint>

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

constexpr auto to_index(const vector<2, int64_t>& pos, int64_t cols) -> int64_t {
	return (pos.x * cols) + pos.y;
}

constexpr auto from_index(int64_t index, int64_t cols) -> vector<2, int64_t> {
	return {index / cols, index % cols};
}

constexpr auto in_bounds(const vector<2, int64_t>& pos, const vector<2, int64_t>& size) -> bool {
	return pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y;
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
