#include "CircleCollider.h"
#include"RectCollider.h"
#include"Object.h"

bool CircleCollider::collide_with(Collider* c, Vec2& force, double& moment) {
	if (c->shape == ColliderShape::Circle) {
		double dis2 = obj->position.dis2(c->obj->position);
		double rd = radius + dynamic_cast<CircleCollider*>(c)->radius;
		if (dis2 > rd*rd) return false;
		double ins = rd - sqrt(dis2);
		Vec2 dir = (obj->position - c->obj->position).normalize();
		force = dir * ins;//
		return true;
	}
	else if (c->shape == ColliderShape::Rect) {
		RectCollider* rc = dynamic_cast<RectCollider*>(c);
		for (int cor = 0; cor < 4; cor++) {
			Vec2 se_cor = rc->get_corner_pos(cor);
			double dis2 = se_cor.dis2(obj->position);
			if (dis2 > radius*radius) continue;
			Vec2 dir = (se_cor - obj->position).normalize();
			force = dir * (sqrt(dis2) - radius);
			return true;
		}
		Vec2 dir = rc->obj->position - obj->position;
		Vec2 tdu = rc->get_dir(0), tdr = rc->get_dir(1);
		double cu = dir.dot(tdu), cr = dir.dot(tdr);
		double hc = rc->height + radius, wc = rc->width + radius;
		if (cu > hc || cu<-hc || cr>wc || cr < -wc) return false;
		if (cu<hc && cu>-hc && cr<rc->width && cr>-rc->width) {
			if (cu > 0) force = tdu * (cu - hc);
			else force = tdu * (cu + hc);
			moment = dir.cross(force);//可证明与理论一致
			//printf("b: %d %.4lf\n", cc->obj->idx, moment);
			return true;
		}
		else if (cr<wc && cr>-wc && cu<rc->height && cu>-rc->height) {
			if (cr > 0) force = tdr * (cr - wc);
			else force = tdr * (cr + wc);
			moment = dir.cross(force);
			//printf("c: %d %.4lf\n", cc->obj->idx, moment);
			return true;
		}
		return false;
	}
	return false;
}
