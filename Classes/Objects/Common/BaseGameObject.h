#pragma once
#include "Cocos/BodySprite.h"
enum class GameObjectType
{
	DEFAULT,
	PLAYER
};
class BaseGameObject
{
public:
	virtual void init();
	virtual void update(float dt);
	void addToWorld(Layer *world);
	void addBodySprite(BodySprite *bodySprite);
	BodySprite *getSpriteByName(const std::string &name) const;

	virtual GameObjectType getType() const;
protected:
	std::vector<BodySprite*> _sprites;
};