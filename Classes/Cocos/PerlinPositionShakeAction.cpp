#include "PerlinPositionShakeAction.h"

PerlinShakeAction::PerlinShakeAction()
{
}

PerlinShakeAction::~PerlinShakeAction()
{
}

PerlinShakeAction* PerlinShakeAction::create()
{
	float duration = 0.8f;
	float speed = 6.0f;
	float magnitude = 4.0f;

	PerlinShakeAction* pAction = new PerlinShakeAction();
	pAction->_duration = duration;
	pAction->_magnitude = magnitude;
	pAction->_speed = speed;

	pAction->initWithDuration(duration);
	pAction->autorelease();
	return pAction;
}
PerlinShakeAction* PerlinShakeAction::create(float duration, float speed, float magnitude)
{
	
	PerlinShakeAction* pAction = new PerlinShakeAction();
	pAction->_duration = duration;
	pAction->_magnitude = magnitude;
	pAction->_speed = speed;

	pAction->initWithDuration(duration);
	pAction->autorelease();
	return pAction;
}

PerlinShakeAction* PerlinShakeAction::create(float speed, float magnitude)
{
	PerlinShakeAction* pAction = new PerlinShakeAction();
	pAction->_duration = std::numeric_limits<float>::max();
	pAction->_magnitude = magnitude;
	pAction->_speed = speed;

	pAction->initWithDuration(std::numeric_limits<float>::max());
	pAction->autorelease();
	return pAction;
}

double PerlinShakeAction::interpolate(double a, double b, double x)
{
	double ft = x * 3.1415927;
	double f = (1.0 - cos(ft))* 0.5;
	return a*(1.0 - f) + b*f;
}

double PerlinShakeAction::findnoise(double x, double y)
{
	int n = (int)x + (int)y * 57;
	n = (n << 13) ^ n;
	int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

double PerlinShakeAction::noise(double x, double y)
{
	double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.
	double floory = (double)((int)y);
	double s, t, u, v;//Integer declaration
	s = findnoise(floorx, floory);
	t = findnoise(floorx + 1, floory);
	u = findnoise(floorx, floory + 1);//Get the surrounding pixels to calculate the transition.
	v = findnoise(floorx + 1, floory + 1);

	double int1 = MathUtil::lerp(s, t, x - floorx);
	double int2 = MathUtil::lerp(u, v, x - floorx);
	return MathUtil::lerp(int1, int2, y - floory);
}

void PerlinShakeAction::setMagnitude(float magnitude)
{
	_magnitude = magnitude;
}

void PerlinShakeAction::setSpeed(float speed)
{
	_speed = speed;
}

void PerlinShakeAction::update(float dt)
{
	static float elapsed = 0.0f;
	float randomStart = random(-1000.0f, 1000.0f);

	if (_target)
	{
		if (!_oriPosSet)
		{
			_orgPos = _target->getPosition();
			_oriPosSet = true;
		}

		elapsed += dt;

		float percentComplete = elapsed / _duration;

		// We want to reduce the shake from full power to 0 starting half way through
		float damper = 1.0f - clampf(2.0f * percentComplete - 1.0f, 0.0f, 1.0f);

		// Calculate the noise parameter starting randomly and going as fast as speed allows
		float alpha = randomStart + _speed * percentComplete;

		// map noise to [-1, 1]
		float x = noise(alpha, 0.0f) * 2.0f - 1.0f;
		float y = noise(0.0f, alpha) * 2.0f - 1.0f;

		x *= _magnitude * damper;
		y *= _magnitude * damper;
		
		auto contentPos = Vec2(x, y);

		float direct = -1.0f;

		if (_direction)
		{
			direct = 1.0f;
			_direction = false;
		}
		else
			_direction = true;

		_target->setPosition(_target->getPosition() + contentPos * direct);//Here is where the magic goes
	
		if (elapsed >= _duration)
		{
			elapsed = 0;
			_target->unscheduleUpdate();			
			_target->runAction(MoveTo::create(1.0f, _orgPos));
		}
	}
}


void PerlinShakeAction::stop()
{
	if (_target)
	{
		_target->unscheduleUpdate();
		_target->runAction(MoveTo::create(1.0f, _orgPos));
	}

	ActionInterval::stop();
}