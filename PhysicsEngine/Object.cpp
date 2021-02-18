#include"Object.h"
#include<vector>
using namespace std;

extern vector<Object*> objs;

void Object::draw() {
	shape->draw(position, rotate);
}

void Object::kinetic(Vec2& acc, double& m) {
	acc = Vec2(0, mass*0.2);//����
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