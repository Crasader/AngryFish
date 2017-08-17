#pragma once
#include "../Common/BaseGameObject.h"
#include "Physics/MyBody.h"

class Player : public BaseGameObject
{
public:
	static const std::string MAIN_SPRITE_NAME;
	virtual void init() override;
	virtual void update(float dt) override;
	virtual GameObjectType getType() const override;

	void setTarget(Vec2 target);
private:
	BodySprite *_mainSprite;
	MyBody *_mainBody;
	float _angularSpeed = 250.0f;
	Vec2 _target = Vec2(0.0f, 0.0f);
};