#ifndef COMMON_HPP
#define COMMON_HPP

#include "vector.hpp"

#include <cmath>
#include <cstdlib>

template <typename T>
constexpr auto abs(const vector<2, T>& v) -> vector<2, T> {
	return {std::abs(v.x), std::abs(v.y)};
}

template <typename T>
constexpr auto dot(const vector<2, T>& a, const vector<2, T>& b) -> T {
	return (a.x * b.x) + (a.y * b.y);
}

template <typename T>
constexpr auto length(const vector<2, T>& a) -> T {
	return std::sqrt(dot(a, a));
}

#endif // !COMMON_HPP
