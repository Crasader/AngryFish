/*
* PerlinShakeAction.h
*
*  Created on: Mar 18, 2016
*      Author: OscarLeif
*/

#ifndef PerlinShakeAction_H_
#define PerlinShakeAction_H_
#include "cocos2d.h"
using namespace cocos2d;
class WorldCamera;

class PerlinShakeAction :public cocos2d::ActionInterval
{
public:
	PerlinShakeAction();
	virtual ~PerlinShakeAction();
	static PerlinShakeAction* create();
	static PerlinShakeAction* create(float duration, float speed, float magnitude);
	static PerlinShakeAction* create(float speed, float magnitude);
	double interpolate(double a, double b, double x);

	double findnoise(double x, double y);

	double noise(double x, double y);
	
	void setMagnitude(float magnitude);
	void setSpeed(float speed);
private:
	float _duration;
	float _speed;
	float _magnitude;
	cocos2d::Vec2 _orgPos;
	bool _oriPosSet = false;
	bool _direction = false;
protected:
	virtual void update(float dt);
	void stop() override;
};


#endif /* PerlinShakeAction_H_ */