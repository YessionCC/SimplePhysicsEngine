#include"Object.h"
#include<vector>
using namespace std;

extern vector<Object*> objs;

void Object::draw(bool show_speed) {
	shape->draw(position, rotate, color);
	if (show_speed) velocity.show_on_screen(position, RED);
}

void Object::kinetic(Vec2& acc, double& m) {
	acc = Vec2(0, mass*0.2);//����
	/*Vec2 dir = (Vec2(250, 250) - position).normalize();
	double exc = Vec2(250, 250).dis2(position);
	acc = dir * (20000.0/exc);*/

	acc = acc - velocity * 0.01;//����
	Vec2 force; double moment = 0;
	for (int i = 0; i < objs.size(); i++) {//��ײ���
		if (i == idx || !objs[i]->is_kinetic) continue;
		bool res = collider->collide_with(objs[i]->collider, force, moment);
		if (!res) continue;
		double dir = force.dot(velocity);
		if (dir < 0) acc = acc + force * 15;//��ѹ����
		else acc = acc + force * 5;//�ظ�����
		m += moment*0.006;//
	}
}