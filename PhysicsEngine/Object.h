#pragma once
#include"Utils.h"
#include"Collider.h"
#include"Shape.h"

class Object {
public:
	int idx;
	double mass;
	Vec2 position;
	Vec2 velocity;
	double angle_vel;
	double rotate;
	Collider* collider;
	Shape* shape;
	bool is_kinetic;//参与动力学
	bool is_static;//是否冻结
public:
	Object(double mass, Collider* col, Shape* shape, Vec2 pos, Vec2 vel = 0, bool sta = false, bool kin = true) :
		angle_vel(0), rotate(0), mass(mass), position(pos), collider(col), shape(shape), velocity(vel), is_kinetic(kin), is_static(sta) {
		collider->obj = this;
	}

	void draw();

	void kinetic(Vec2& acc, double& m);
};