#pragma once
#include"Utils.h"

enum ColliderShape {
	Circle,
	Rect
};
class Object;

class Collider {//circle
public:
	Object* obj;
	ColliderShape shape;
	Collider(ColliderShape shape) : shape(shape) {}
	virtual bool collide_with(Collider* c, Vec2& force, double& moment) { return false; }
};
