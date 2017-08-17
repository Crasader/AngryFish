#include "Player.h"
#include "Math/AngleHelper.h"

const std::string Player::MAIN_SPRITE_NAME = "MainSprite";

void Player::init()
{
	_mainSprite = getSpriteByName(MAIN_SPRITE_NAME);
	_mainBody = _mainSprite->getBody();
}

void Player::update(float dt)
{
	Vec2 diff = _mainBody->getPosition() - _target;
	float angle = 180.0f - CC_RADIANS_TO_DEGREES(diff.getAngle()) - 90.0f;
	float angleDiff = AngleHelper::getSmallestDifference(_mainBody->getAngle(), angle);
	float angularVelocity = std::min(fabs(angleDiff) / dt, _angularSpeed);
	angularVelocity *= angleDiff < 0.0f ? -1.0f : 1.0f;
	_mainBody->setAngularVelocity(angularVelocity);
}

GameObjectType Player::getType() const
{
	return GameObjectType::PLAYER;
}

void Player::setTarget(Vec2 target)
{
	_target = target;
}
