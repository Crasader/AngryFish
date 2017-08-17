#include "BaseGameObject.h"

BaseGameObject::~BaseGameObject()
{

}

void BaseGameObject::init()
{

}

void BaseGameObject::update(float dt)
{

}

void BaseGameObject::addToWorld(Layer *world)
{
	for (auto &sprite : _sprites)
	{
		world->addChild(sprite);
	}
}

void BaseGameObject::addBodySprite(BodySprite *bodySprite)
{
	_sprites.push_back(bodySprite);
}

BodySprite * BaseGameObject::getSpriteByName(const std::string &name) const
{
	return *std::find_if(_sprites.begin(), _sprites.end(), [=](const BodySprite *sprite)
	{
		return name == sprite->getSpriteName();
	});
}

void BaseGameObject::destroy()
{

}

GameObjectType BaseGameObject::getType() const
{
	return GameObjectType::DEFAULT;
}
