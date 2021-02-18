#include "RectCollider.h"
#include"CircleCollider.h"
#include"Object.h"
#include<cstdio>

bool RectCollider::check_corner_to_self(Vec2 corner, RectCollider* rc, Vec2& tdu, Vec2& tdr, Vec2& force, double& moment) {
	Vec2 f;
	Vec2 dir = corner - obj->position;
	double cu = dir.dot(tdu), cr = dir.dot(tdr);
	if (cu > height || cu<-height || cr>width || cr < -width) return false;
	if (height - abs(cu) < width - abs(cr)) {
		if (cu > 0) f = tdu * (cu - height);
		else f = tdu * (cu + height);
		moment += dir.cross(f);
	}
	else {
		if (cr > 0) f = tdr * (cr - width);
		else f = tdr * (cr + width);
		moment += dir.cross(f);
	}
	force = force + f;
	return true;
}

bool RectCollider::check_corner_to_other(Vec2 corner, RectCollider* rc, Vec2& otdu, Vec2& otdr, Vec2& force, double& moment) {
	Vec2 f;
	Vec2 dir = corner - rc->obj->position;
	Vec2 sdir = corner - obj->position;
	double cu = dir.dot(otdu), cr = dir.dot(otdr);
	if (cu >= rc->height || cu <= -rc->height || cr >= rc->width || cr <= -rc->width) return false;
	if (rc->height - abs(cu) < rc->width - abs(cr)) {
		if (cu > 0) f = otdu * (rc->height - cu);
		else f = otdu * (-cu - rc->height);
		moment += sdir.cross(f);
	}
	else {
		if (cr > 0) f = otdr * (rc->width - cr);
		else f = otdr * (-cr - rc->width);
		moment += sdir.cross(f);
	}
	force = force + f;
	return true;
}

bool RectCollider::collide_with(Collider* c, Vec2 & force, double & moment) {
	if (c->shape == ColliderShape::Rect) {
		bool ret = false; Vec2 f;
		RectCollider* rc = dynamic_cast<RectCollider*>(c);
		Vec2 tdu = get_dir(0), tdr = get_dir(1);
		Vec2 otdu = rc->get_dir(0), otdr = rc->get_dir(1);
		for (int cor = 0; cor < 4; cor++) {//判角与面接触
			bool res = check_corner_to_self(rc->get_corner_pos(cor), rc, tdu, tdr, force, moment);
			if (res) {//偏移检测在主检测到后进行，避免不必要的计算，偏移检测避免角接触后碰撞失效
				check_corner_to_self(rc->get_corner_pos(cor + 4), rc, tdu, tdr, force, moment);
				check_corner_to_self(rc->get_corner_pos(cor + 8), rc, tdu, tdr, force, moment);
				ret = true;
			}
		}
		for (int cor = 0; cor < 4; cor++) {//判面与角接触
			bool res = check_corner_to_other(get_corner_pos(cor), rc, otdu, otdr, force, moment);
			if (res) {
				check_corner_to_other(get_corner_pos(cor + 4), rc, otdu, otdr, force, moment);
				check_corner_to_other(get_corner_pos(cor + 8), rc, otdu, otdr, force, moment);
				ret = true;
			}
		}
		return ret;
	}
	else if (c->shape == ColliderShape::Circle) {
		CircleCollider* cc = dynamic_cast<CircleCollider*>(c);
		Vec2 f; bool ret = false;
		for (int cor = 0; cor < 4; cor++) {
			Vec2 se_cor = get_corner_pos(cor);
			double dis2 = se_cor.dis2(cc->obj->position);
			if (dis2 > cc->radius*cc->radius) continue;
			Vec2 dir = (se_cor - cc->obj->position).normalize();
			Vec2 sdir = se_cor - obj->position;
			f = dir * (cc->radius - sqrt(dis2));
			moment += sdir.cross(f);
			force = force + f;//可能两点同时落入碰撞，避免异常弹跳
			ret = true;
		}
		if (ret) return true;
		Vec2 dir = cc->obj->position - obj->position;
		Vec2 tdu = get_dir(0), tdr = get_dir(1);
		double cu = dir.dot(tdu), cr = dir.dot(tdr);
		double hc = height + cc->radius, wc = width + cc->radius;
		//if (cu > hc || cu<-hc || cr>wc || cr < -wc) return false;
		if (cu<hc && cu>-hc && cr<width && cr>-width) {//重要判据
			if (cu > 0) force = tdu * (cu - hc);
			else force = tdu * (cu + hc);
			moment = dir.cross(force);//可证明与理论一致
			//printf("b: %d %.4lf\n", cc->obj->idx, moment);
			return true;
		}
		else if(cr<wc && cr>-wc && cu<height && cu>-height){
			if (cr > 0) force = tdr * (cr - wc);
			else force = tdr * (cr + wc);
			moment = dir.cross(force);
			//printf("c: %d %.4lf\n", cc->obj->idx, moment);
			return true;
		}
	}
	return false;
}

Vec2 RectCollider::get_corner_pos(int which) {
	switch (which) {
	case 0: return obj->position + Vec2(width, height).rotate(obj->rotate);
	case 1: return obj->position + Vec2(width, -height).rotate(obj->rotate);
	case 2: return obj->position + Vec2(-width, height).rotate(obj->rotate);
	case 3: return obj->position + Vec2(-width, -height).rotate(obj->rotate);

	case 4: return obj->position + Vec2(width*0.5, height).rotate(obj->rotate);//防止边角陷入
	case 5: return obj->position + Vec2(width*0.5, -height).rotate(obj->rotate);
	case 6: return obj->position + Vec2(-width*0.5, height).rotate(obj->rotate);
	case 7: return obj->position + Vec2(-width*0.5, -height).rotate(obj->rotate);

	case 8: return obj->position + Vec2(width, height*0.5).rotate(obj->rotate);
	case 9: return obj->position + Vec2(width, -height*0.5).rotate(obj->rotate);
	case 10: return obj->position + Vec2(-width, height*0.5).rotate(obj->rotate);
	case 11: return obj->position + Vec2(-width, -height*0.5).rotate(obj->rotate);

	default: return Vec2();
	}
}

Vec2 RectCollider::get_dir(int which) {
	if (which == 0) return Vec2(0, 1).rotate(obj->rotate);
	else return Vec2(1, 0).rotate(obj->rotate);
}
