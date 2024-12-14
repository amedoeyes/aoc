#ifndef TO_STRING_HPP
#define TO_STRING_HPP

#include "vector2.hpp"

#include <format>
#include <string>

template <typename T>
constexpr auto to_string(const vector<2, T>& v) -> std::string {
	return std::format("({}, {})", v.x, v.y);
}

#endif // !TO_STRING_HPP
