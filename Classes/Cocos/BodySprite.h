#pragma once
#include "cocos2d.h"
#include "Physics/MyBody.h"
using namespace cocos2d;

class BodySprite : public Sprite
{
public:
	static BodySprite *create(MyBody *body, std::string imagePath);
	BodySprite(MyBody *body);
	virtual bool initWithFile(const std::string& filename);
	void update(float delta);

	void setSpriteName(const std::string &name);
	std::string getSpriteName() const;

	MyBody *getBody() const;
protected:
	MyBody *_body;
	std::string _name;
};