#pragma once
#include<cmath>
#include<cstdio>

struct Vec2 {
	double x, y;
	double dot(Vec2 v) { return v.x*x + v.y*y; }
	double cross(Vec2 v) { return x * v.y - y * v.x; }
	Vec2 operator+(Vec2 v) { return Vec2{ v.x + x, v.y + y }; }
	Vec2 operator-(Vec2 v) { return Vec2{ x - v.x, y - v.y }; }
	Vec2 operator*(double v) { return Vec2{ v * x, v * y }; }
	double dis2(Vec2 v) { double dx = v.x - x, dy = v.y - y; return dx * dx + dy * dy; }
	double dis(Vec2 v) { double dx = v.x - x, dy = v.y - y; return sqrt(dx * dx + dy * dy); }
	Vec2& normalize() { double n = sqrt(x*x + y * y); x /= n; y /= n; return *this; }
	Vec2 rotate(double a) { return Vec2(cos(a)*x - sin(a)*y, sin(a)*x + cos(a)*y); }
	Vec2(double x = 0, double y = 0) : x(x), y(y) {}
	bool is_zero() { return abs(x) < 1e-5 && abs(y) < 1e-5; }
	void print() { printf("%.4lf %.4lf\n", x, y); }
};
