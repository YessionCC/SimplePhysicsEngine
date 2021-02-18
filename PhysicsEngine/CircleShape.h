#pragma once
#include"Shape.h"

class CircleShape : public Shape {
public:
	double radius;
	CircleShape(double radius) : radius(radius) {}
	virtual void draw(Vec2& pos, double rotate) {
		circle(pos.x, pos.y, radius);
	}
};
