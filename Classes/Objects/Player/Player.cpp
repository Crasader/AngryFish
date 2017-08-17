#include "Player.h"
#include "Math/AngleHelper.h"
#include "StateControllers/PlayerStateController.h"
#include "StateControllers/PlayerIdleStateController.h"
#include "StateControllers/PlayerAttackStateController.h"
#include "StateControllers/PlayerDeathStateController.h"
#include "Sounds/SoundManager.h"

const std::string Player::MAIN_SPRITE_NAME = "MainSprite";

const std::string Player::TEXTURE_FISH = "textures/fish.png";

const std::string Player::TEXTURE_FISH_ATTACK = "textures/fishBubble.png";

Player::~Player()
{
	for (auto &stateController : _stateControllers)
	{
		delete stateController;
	}
}

void Player::init()
{
	_mainSprite = getSpriteByName(MAIN_SPRITE_NAME);
	_mainBody = _mainSprite->getBody();
	_idleTexture = TextureCache::getInstance()->addImage(TEXTURE_FISH);
	_attackTexture = TextureCache::getInstance()->addImage(TEXTURE_FISH_ATTACK);
	initStateControllers();
	setIdleState();
}

void Player::update(float dt)
{
	_currentReloadTime += dt;
	if (_currentStateController)
	{
		_currentStateController->update(dt);
	}
}

void Player::updateRotation(float dt)
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

BodySprite * Player::getMainSprite() const
{
	return _mainSprite;
}

MyBody * Player::getMainBody() const
{
	return _mainBody;
}

float Player::getBubbleSpeed() const
{
	return _bubbleSpeed;
}

void Player::attack()
{
	sendStateCommand(PlayerStateCommand::ATTACK);
}

void Player::setCurrentStateController(PlayerStateController *stateController)
{
	if (_currentStateController)
	{
		_currentStateController->exit();
	}
	_currentStateController = stateController;
	if (_currentStateController)
	{
		_currentStateController->setPlayer(this);
		_currentStateController->enter();
	}
}

void Player::sendStateCommand(PlayerStateCommand commandType, void *data /*= nullptr*/)
{
	if (_currentStateController)
	{
		_currentStateController->executeCommand(commandType, data);
	}
}

void Player::tryToAttack()
{
	if (_currentReloadTime >= _reloadTime)
	{
		resetCurrentReloadTime();
		setAttackState();
	}
}

void Player::setAttackState()
{
	setCurrentStateController(_attackStateController);
}

void Player::setIdleState()
{
	setCurrentStateController(_idleStateController);
}

void Player::setDeathState()
{
	setCurrentStateController(_deathStateController);
}

void Player::setIdleAnimation()
{
	_mainSprite->setTexture(_idleTexture);
}

void Player::setAttackAnimation()
{
	_mainSprite->setTexture(_attackTexture);
}

void Player::resetCurrentReloadTime()
{
	_currentReloadTime = 0.0f;
}

void Player::playAttackSound()
{
	SoundManager::getInstance()->playBubbleAttackSound();
}

void Player::notifyDeathEvent()
{
	if (onDeathEvent)
		onDeathEvent();
}

void Player::notifyShootEvent()
{
	if (onShoot)
		onShoot();
}

void Player::initStateControllers()
{
	_idleStateController = new PlayerIdleStateController();
	_attackStateController = new PlayerAttackStateController();
	_deathStateController = new PlayerDeathStateController();
	_stateControllers.insert(_stateControllers.begin(), {_idleStateController, _attackStateController, _deathStateController});
}
