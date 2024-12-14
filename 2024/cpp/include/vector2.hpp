#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "vector.hpp"

template <typename T>
struct vector<2, T> {
	constexpr vector() : x(0), y(0) {};
	constexpr explicit vector(T s) : x(s), y(s) {};
	constexpr vector(T a, T b) : x(a), y(b) {};
	union {
		T x, r, s;
	};
	union {
		T y, g, t;
	};
};

// unary

template <typename T>
constexpr auto operator+(const vector<2, T>& v) -> vector<2, T> {
	return v;
}

template <typename T>
constexpr auto operator-(const vector<2, T>& v) -> vector<2, T> {
	return {-v.x, -v.y};
}

template <typename T>
constexpr auto operator++(vector<2, T>& v) -> vector<2, T>& {
	++v.x;
	++v.y;
	return v;
}

template <typename T>
constexpr auto operator--(vector<2, T>& v) -> vector<2, T>& {
	--v.x;
	--v.y;
	return v;
}

// binary scalar

template <typename T>
constexpr auto operator+(const vector<2, T>& v, T s) -> vector<2, T> {
	return {v.x + s, v.y + s};
}

template <typename T>
constexpr auto operator+(T s, const vector<2, T>& v) -> vector<2, T> {
	return {s + v.x, s + v.y};
}

template <typename T>
constexpr auto operator-(const vector<2, T>& v, T s) -> vector<2, T> {
	return {v.x - s, v.y - s};
}

template <typename T>
constexpr auto operator-(T s, const vector<2, T>& v) -> vector<2, T> {
	return {s - v.x, s - v.y};
}

template <typename T>
constexpr auto operator*(const vector<2, T>& v, T s) -> vector<2, T> {
	return {v.x * s, v.y * s};
}

template <typename T>
constexpr auto operator*(T s, const vector<2, T>& v) -> vector<2, T> {
	return {s * v.x, s * v.y};
}

template <typename T>
constexpr auto operator/(const vector<2, T>& v, T s) -> vector<2, T> {
	return {v.x / s, v.y / s};
}

template <typename T>
constexpr auto operator/(T s, const vector<2, T>& v) -> vector<2, T> {
	return {s / v.x, s / v.y};
}

template <typename T>
constexpr auto operator%(const vector<2, T>& v, T s) -> vector<2, T> {
	return {v.x % s, v.y % s};
}

template <typename T>
constexpr auto operator%(T s, const vector<2, T>& v) -> vector<2, T> {
	return {s % v.x, s % v.y};
}

template <typename T>
constexpr auto operator+=(vector<2, T>& v, T s) -> vector<2, T>& {
	v.x += s;
	v.y += s;
	return v;
}

template <typename T>
constexpr auto operator-=(vector<2, T>& v, T s) -> vector<2, T>& {
	v.x -= s;
	v.y -= s;
	return v;
}

template <typename T>
constexpr auto operator*=(vector<2, T>& v, T s) -> vector<2, T>& {
	v.x *= s;
	v.y *= s;
	return v;
}

template <typename T>
constexpr auto operator/=(vector<2, T>& v, T s) -> vector<2, T>& {
	v.x /= s;
	v.y /= s;
	return v;
}

template <typename T>
constexpr auto operator%=(vector<2, T>& v, T s) -> vector<2, T>& {
	v.x %= s;
	v.y %= s;
	return v;
}

// binary vector2

template <typename T>
constexpr auto operator+(const vector<2, T>& l, const vector<2, T>& r) -> vector<2, T> {
	return {l.x + r.x, l.y + r.y};
}

template <typename T>
constexpr auto operator-(const vector<2, T>& l, const vector<2, T>& r) -> vector<2, T> {
	return {l.x - r.x, l.y - r.y};
}

template <typename T>
constexpr auto operator*(const vector<2, T>& l, const vector<2, T>& r) -> vector<2, T> {
	return {l.x * r.x, l.y * r.y};
}

template <typename T>
constexpr auto operator/(const vector<2, T>& l, const vector<2, T>& r) -> vector<2, T> {
	return {l.x / r.x, l.y / r.y};
}

template <typename T>
constexpr auto operator%(const vector<2, T>& l, const vector<2, T>& r) -> vector<2, T> {
	return {l.x % r.x, l.y % r.y};
}

template <typename T>
constexpr auto operator+=(vector<2, T>& l, const vector<2, T>& r) -> vector<2, T>& {
	l.x += r.x;
	l.y += r.y;
	return l;
}

template <typename T>
constexpr auto operator-=(vector<2, T>& l, const vector<2, T>& r) -> vector<2, T>& {
	l.x -= r.x;
	l.y -= r.y;
	return l;
}

template <typename T>
constexpr auto operator*=(vector<2, T>& l, const vector<2, T>& r) -> vector<2, T>& {
	l.x *= r.x;
	l.y *= r.y;
	return l;
}

template <typename T>
constexpr auto operator/=(vector<2, T>& l, const vector<2, T>& r) -> vector<2, T>& {
	l.x /= r.x;
	l.y /= r.y;
	return l;
}

template <typename T>
constexpr auto operator%=(vector<2, T>& l, const vector<2, T>& r) -> vector<2, T>& {
	l.x %= r.x;
	l.y %= r.y;
	return l;
}

// binary boolean

template <typename T>
constexpr auto operator==(const vector<2, T>& l, const vector<2, T>& r) -> bool {
	return l.x == r.x && l.y == r.y;
}

template <typename T>
constexpr auto operator!=(const vector<2, T>& l, const vector<2, T>& r) -> bool {
	return l.x != r.x || l.y != r.y;
}

#endif // !VECTOR2_HPP
