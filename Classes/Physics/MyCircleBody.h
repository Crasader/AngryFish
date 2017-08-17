#pragma once
#include "MyBody.h"

class MyCircleBody : public MyBody
{
public:
	virtual MyBodyType getType() const override;
	void setRadius(float radius);
	float getRadius() const;
private:
	float _radius = 1.0f;
};