#pragma once
#include"Utils.h"
#include"Collider.h"
#include"CircleCollider.h"
#include"RectCollider.h"
#include"Shape.h"
#include"CircleShape.h"
#include"RectShape.h"

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
	COLORREF color;
	bool is_kinetic;//参与动力学
	bool is_static;//是否冻结
public:
	Object(double mass, Collider* col, Shape* shape, Vec2 pos, Vec2 vel = 0, bool sta = false, bool kin = true) :
		angle_vel(0), rotate(0), mass(mass), position(pos), 
		collider(col), shape(shape), velocity(vel), 
		is_kinetic(kin), is_static(sta), color(BLACK) {
		collider->obj = this;
	}

	Object(double mass, Collider* col, Vec2 pos, Vec2 vel = 0, bool sta = false, bool kin = true) :
		angle_vel(0), rotate(0), mass(mass), position(pos), 
		collider(col), velocity(vel), is_kinetic(kin), 
		is_static(sta), color(BLACK) {
		collider->obj = this;
		if (col->shape == ColliderShape::Circle) {
			CircleCollider* cc = dynamic_cast<CircleCollider*>(col);
			shape = new CircleShape(cc->radius);
		}
		else if (col->shape == ColliderShape::Rect) {
			RectCollider* rc = dynamic_cast<RectCollider*>(col);
			shape = new RectShape(rc->width * 2, rc->height * 2);
		}
	}

	virtual ~Object() {
		delete collider;
		delete shape;
	}

	void draw(bool show_speed=false);

	void kinetic(Vec2& acc, double& m);
};