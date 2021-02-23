#pragma once
#include"Shape.h"

class CircleShape : public Shape {
public:
	double radius;
	CircleShape(double radius) : radius(radius) {}
	virtual void draw(Vec2& pos, double rotate, COLORREF color) {
		setlinecolor(color);
		circle(pos.x, pos.y, radius);
	}
};
