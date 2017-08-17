#include "BodySprite.h"

BodySprite * BodySprite::create(MyBody *body, std::string imagePath)
{
	BodySprite *sprite = new BodySprite(body);
	if (sprite && sprite->initWithFile(imagePath))
	{
		sprite->autorelease(); 
		return sprite; 
	} 
	else
	{
		delete sprite;
		sprite = nullptr;
		return nullptr;
	}
}

BodySprite::BodySprite(MyBody *body) : _body(body)
{

}


bool BodySprite::initWithFile(const std::string& filename)
{
	if (Sprite::initWithFile(filename) == false)
	{ 
		return false;
	}
	scheduleUpdate();
	return true;
}

void BodySprite::update(float delta)
{
	this->setPosition(_body->getPosition());
	this->setRotation(_body->getAngle());
}

void BodySprite::setSpriteName(const std::string &name)
{
	_name = name;
}

std::string BodySprite::getSpriteName() const
{
	return _name;
}

MyBody * BodySprite::getBody() const
{
	return _body;
}
