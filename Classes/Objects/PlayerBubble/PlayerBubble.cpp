#include "PlayerBubble.h"

const std::string PlayerBubble::IMAGE_PATH = "textures/bubble.png";

const std::string PlayerBubble::MAIN_SPRITE_NAME = "MainSprite";

void PlayerBubble::init()
{
	_mainSprite = getSpriteByName(MAIN_SPRITE_NAME);
	setFly();
}

void PlayerBubble::update(float dt)
{

}

GameObjectType PlayerBubble::getType() const
{
	return GameObjectType::PLAYER_BUBBLE;
}

void PlayerBubble::setFly()
{
	_state = PlayerBubbleState::FLY;
	_mainSprite->runAction(RepeatForever::create(Sequence::create(ScaleBy::create(0.1f, 1.1f), ScaleBy::create(0.1f, 1.0f / 1.1f), nullptr)));
}

void PlayerBubble::setDeath()
{
	_state = PlayerBubbleState::DEATH;
	_mainSprite->runAction(Sequence::create(FadeOut::create(0.4f), CallFunc::create([&](){
		_mainSprite->removeFromParentAndCleanup(true);
		notifyDeathEvent();
	}), nullptr));
}

void PlayerBubble::notifyDeathEvent()
{
	if (onDeath)
		onDeath();
}
