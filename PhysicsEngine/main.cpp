#include<graphics.h>
#include<vector>
#include<random>
#include"Object.h"
#include"CircleCollider.h"
#include"CircleShape.h"
#include"RectCollider.h"
#include"RectShape.h"
using namespace std;

int width = 500;
int height = 500;

vector<Object*> objs;

void init_scene() {
	for (int i = 0; i < 300; i += 120) {
		objs.push_back(new Object(10, new RectCollider(80, 30), new RectShape(80, 30), Vec2(80, 80+i)));
		objs.push_back(new Object(10, new RectCollider(30, 90), new RectShape(30, 90), Vec2(150, 80+i)));
		objs.push_back(new Object(10, new RectCollider(80, 30), new RectShape(80, 30), Vec2(220, 80+i)));
		objs.push_back(new Object(10, new RectCollider(30, 90), new RectShape(30, 90), Vec2(300, 80+i)));
	}
	objs.push_back(new Object(20, new CircleCollider(20), new CircleShape(20), Vec2(400, 50), Vec2(-10, 0)));
	
	objs.push_back(new Object(10, new RectCollider(1800, 60), new RectShape(1800, 60), Vec2(250, 450), 0, true));
	objs.push_back(new Object(10, new RectCollider(60, 1800), new RectShape(60, 1800), Vec2(0, 450), 0, true));
	objs.push_back(new Object(10, new RectCollider(60, 1800), new RectShape(60, 1800), Vec2(500, 450), 0, true));


	/*objs.push_back(new Object(10, new CircleCollider(800), new CircleShape(800), Vec2(-750, 220), 0, true));
	objs.push_back(new Object(10, new CircleCollider(800), new CircleShape(800), Vec2(1250, 220), 0, true));
	objs.push_back(new Object(10, new CircleCollider(800), new CircleShape(800), Vec2(250, 1250), 0, true));
	objs.push_back(new Object(10, new CircleCollider(800), new CircleShape(800), Vec2(250, -750), 0, true));*/
	for (int i = 0; i < objs.size(); i++) objs[i]->idx = i;
}

void update(double dt = 0.003) {
	vector<Vec2> acs;
	vector<double> ms;
	for (Object* obj : objs) {
		Vec2 acc; double moment = 0;
		obj->kinetic(acc, moment);
		acs.push_back(acc);
		ms.push_back(moment);
	}
	for (int i = 0; i < objs.size(); i++) {
		Object* obj = objs[i];
		if (obj->is_static) continue;
		obj->velocity = obj->velocity + acs[i] * dt;
		obj->position = obj->position + obj->velocity*dt;
		obj->angle_vel += ms[i] * dt;
		obj->rotate += obj->angle_vel*dt;
		/*if (obj->velocity.is_zero()) obj->velocity = Vec2();
		if (abs(obj->rotate)<1e-5) obj->rotate = 0;*/
	}
}

void draw() {
	for (Object* obj : objs) {
		obj->draw();
	}
}

int main() {
	init_scene();
	initgraph(width, height, 1);
	setlinecolor(BLACK);
	BeginBatchDraw();
	int frame = 0;
	while (true) {
		setbkcolor(WHITE);
		cleardevice();

		//printf("%d\n", ++frame);
		for (int i = 0; i < 100; i++) 
			update(0.0008);
		draw();

		FlushBatchDraw();
	}
	EndBatchDraw();

	system("pause");
	return 0;
}