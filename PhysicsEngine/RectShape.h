#pragma once
#include"Shape.h"

class RectShape : public Shape {
public:
	double width, height;
	RectShape(double w, double h) : width(w/2), height(h/2) {}
	virtual void draw(Vec2& pos, double rotate) {//以pos为中心
		Vec2 p1 = Vec2(width, height).rotate(rotate);
		Vec2 p2 = Vec2(width, -height).rotate(rotate);
		line(p1.x + pos.x, p1.y + pos.y, p2.x + pos.x, p2.y + pos.y);
		line(p1.x + pos.x, p1.y + pos.y, -p2.x + pos.x, -p2.y + pos.y);
		line(-p1.x + pos.x, -p1.y + pos.y, p2.x + pos.x, p2.y + pos.y);
		line(-p1.x + pos.x, -p1.y + pos.y, -p2.x + pos.x, -p2.y + pos.y);
	}

};