#pragma once
#include"Utils.h"
#include<graphics.h>
#include<cmath>


class Shape {
public:
	virtual void draw(Vec2& pos, double rotate) {}
};
