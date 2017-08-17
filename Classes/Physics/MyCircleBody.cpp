#include "MyCircleBody.h"

MyBodyType MyCircleBody::getType() const
{
	return MyBodyType::CIRCLE;
}

void MyCircleBody::setRadius(float radius)
{
	_radius = radius;
}

float MyCircleBody::getRadius() const
{
	return _radius;
}
