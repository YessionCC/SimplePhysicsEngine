#pragma once
#include"Collider.h"

class CircleCollider : public Collider {
public:
	double radius;

	CircleCollider(double radius) : radius(radius), Collider(ColliderShape::Circle) {}
	virtual bool collide_with(Collider* c, Vec2& force, double& moment);
};
