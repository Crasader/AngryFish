#include "MyBody.h"

void MyBody::setPosition(Vec2 position)
{
	_position = position;
}

void MyBody::setAngle(float angle)
{
	_angle = angle;
}

void MyBody::setVelocity(Vec2 velocity)
{
	_velocity = velocity;
}

void MyBody::setAngularVelocity(float angularVelocity)
{
	_angularVelocity = angularVelocity;
}

cocos2d::Vec2 MyBody::getPosition() const
{
	return _position;
}

float MyBody::getAngle() const
{
	return _angle;
}

cocos2d::Vec2 MyBody::getVelocity() const
{
	return _velocity;
}

float MyBody::getAngularVelocity() const
{
	return _angularVelocity;
}

void MyBody::setData(void *data)
{
	_data = data;
}

void * MyBody::getData() const
{
	return _data;
}

void MyBody::setPhysics(MyPhysics *physics)
{
	_physics = physics;
}

MyPhysics *MyBody::getPhysics() const
{
	return _physics;
}
