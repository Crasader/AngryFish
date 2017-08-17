#pragma once
#include "MyBody.h"
#include "MyCircleBody.h"
// Super simple physics engine
class MyPhysics
{
public:
	virtual ~MyPhysics();
	MyCircleBody *createCircleBody(float radius);
	void update(float dt);

	void removeBody(MyBody *body);
	std::function<void(MyBody *, MyBody*)> onCollision = nullptr;
protected:
	bool checkCollision(MyBody *body1, MyBody *body2);
	void notifyCollisionEvent(MyBody *body1, MyBody *body2);
private:
	bool _lockedWorld = false;
	std::vector<MyBody*> _bodies;
};