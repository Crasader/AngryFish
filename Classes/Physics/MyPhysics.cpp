#include "MyPhysics.h"
#include "MyCircleBody.h"

MyPhysics::~MyPhysics()
{
	for (auto body : _bodies)
	{
		delete body;
	}
}

MyCircleBody * MyPhysics::createCircleBody(float radius)
{
	MyCircleBody *circleBody = new MyCircleBody();
	circleBody->setRadius(radius);
	_bodies.push_back(circleBody);
	return circleBody;
}

void MyPhysics::update(float dt)
{
	_lockedWorld = true;
	for (auto body : _bodies)
	{
		Vec2 position = body->getPosition();
		position += body->getVelocity() * dt;
		float angle = body->getAngle();
		angle += body->getAngularVelocity() * dt;
		body->setPosition(position);
		body->setAngle(angle);
	}
	if (_bodies.size() > 1)
	{
		for (int i = 0; i < _bodies.size() - 1; i++)
		{
			for (int j = i + 1; j < _bodies.size(); j++)
			{
				if (checkCollision(_bodies[i], _bodies[j]))
				{
					notifyCollisionEvent(_bodies[i], _bodies[j]);
				}
			}
		}
	}
	_lockedWorld = false;
}

void MyPhysics::removeBody(MyBody *body)
{
	assert(_lockedWorld == false);
	auto foundBody = std::find(_bodies.begin(), _bodies.end(), body);
	if (foundBody != _bodies.end())
	{
		_bodies.erase(foundBody);
		delete *foundBody;
	}
}

bool MyPhysics::checkCollision(MyBody *body1, MyBody *body2)
{
	if (body1->getType() == MyBodyType::CIRCLE && body2->getType() == MyBodyType::CIRCLE)
	{
		MyCircleBody *circleBody1 = static_cast<MyCircleBody*>(body1);
		MyCircleBody *circleBody2 = static_cast<MyCircleBody*>(body2);
		float distance = (circleBody1->getPosition() - circleBody2->getPosition()).length();
		if (distance <= circleBody1->getRadius() + circleBody2->getRadius())
		{
			return true;
		}
	}
	return false;
}

void MyPhysics::notifyCollisionEvent(MyBody *body1, MyBody *body2)
{
	if (onCollision)
	{
		onCollision(body1, body2);
	}
}
