#pragma once
#include "cocos2d.h"
using namespace cocos2d;
enum class MyBodyType
{
	CIRCLE
};
class MyPhysics;
class MyBody
{
public:
	void setPosition(Vec2 position);
	void setAngle(float angle);

	void setVelocity(Vec2 velocity);
	void setAngularVelocity(float angularVelocity);

	Vec2 getPosition() const;
	float getAngle() const;
	Vec2 getVelocity() const;
	float getAngularVelocity() const;

	void setData(void *data);
	void *getData() const;

	void setPhysics(MyPhysics *physics);
	MyPhysics *getPhysics() const;

	virtual MyBodyType getType() const = 0;
protected:
	void *_data = nullptr;
	Vec2 _position = Vec2(0.0f, 0.0f);
	float _angle = 0.0f;
	Vec2 _velocity = Vec2(0.0f, 0.0f);
	float _angularVelocity = 0.0f;
	MyPhysics *_physics = nullptr;
};