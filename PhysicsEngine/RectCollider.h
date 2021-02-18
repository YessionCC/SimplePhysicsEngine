#pragma once
#include"Collider.h"

class RectCollider : public Collider {
public:
	double width, height;
	RectCollider(double w, double h) : width(w / 2), height(h / 2), Collider(ColliderShape::Rect) {}
	virtual bool collide_with(Collider* c, Vec2& force, double& moment);

	bool check_corner_to_self(Vec2 corner, RectCollider* rc, Vec2& tdu, Vec2& tdr, Vec2& force, double& moment);
	bool check_corner_to_other(Vec2 corner, RectCollider* rc, Vec2& otdu, Vec2& otdr, Vec2& force, double& moment);

	Vec2 get_corner_pos(int which);

	Vec2 get_dir(int which);
};