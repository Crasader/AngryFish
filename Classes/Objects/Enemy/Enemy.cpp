#include "Enemy.h"
#include "StateControllers/EnemyStateController.h"
#include "Math/AngleHelper.h"
#include "StateControllers/EnemyDeathStateController.h"
#include "StateControllers/EnemyIdleStateController.h"
#include "Sounds/SoundManager.h"

const std::string Enemy::IMAGE_PATH = "textures/badFish.png";

const std::string Enemy::MAIN_SPRITE_NAME = "MainSprite";

Enemy::~Enemy()
{
	for (auto &stateController : _stateControllers)
	{
		delete stateController;
	}
}

void Enemy::init()
{
	_mainSprite = getSpriteByName(MAIN_SPRITE_NAME);
	_mainBody = _mainSprite->getBody();
	initStateControllers();
	setIdleState();
}

void Enemy::update(float dt)
{
	if (_currentStateController)
	{
		_currentStateController->update(dt);
	}
}

GameObjectType Enemy::getType() const
{
	return GameObjectType::ENEMY;
}

BodySprite * Enemy::getMainSprite() const
{
	return _mainSprite;
}

MyBody * Enemy::getMainBody() const
{
	return _mainBody;
}

EnemyState Enemy::getState() const
{
	if (_currentStateController)
	{
		return _currentStateController->getEnemyState();
	}
	return EnemyState::NONE;
}

void Enemy::updateRotationAndVelocity(float dt)
{
	Vec2 diff = _mainBody->getPosition() - _target;
	float angle = 180.0f - CC_RADIANS_TO_DEGREES(diff.getAngle()) - 90.0f;
	float angleDiff = AngleHelper::getSmallestDifference(_mainBody->getAngle(), angle);
	float angularVelocity = _angularSpeed;
	angularVelocity *= angleDiff < 0.0f ? -1.0f : 1.0f;
	_mainBody->setAngularVelocity(angularVelocity);

	float velocityAngle = CC_DEGREES_TO_RADIANS(180.0f - _mainBody->getAngle() + 90.0f);
	Vec2 velocity = Vec2(cosf(velocityAngle), sinf(velocityAngle));
	velocity *= _movementSpeed;
	_mainBody->setVelocity(velocity);
}

void Enemy::setTarget(Vec2 target)
{
	_target = target;
}

void Enemy::damage()
{
	sendStateCommand(EnemyStateCommand::DAMAGE);
}

void Enemy::setIdleState()
{
	setCurrentStateController(_idleStateController);
}

void Enemy::setDeathState()
{
	setCurrentStateController(_deathStateController);
}

void Enemy::setCurrentStateController(EnemyStateController *stateController)
{
	if (_currentStateController)
	{
		_currentStateController->exit();
	}
	_currentStateController = stateController;
	if (_currentStateController)
	{
		_currentStateController->setEnemy(this);
		_currentStateController->enter();
	}
}

void Enemy::sendStateCommand(EnemyStateCommand commandType, void *data /*= nullptr*/)
{
	if (_currentStateController)
	{
		_currentStateController->executeCommand(commandType, data);
	}
}

void Enemy::playDeathSound()
{
	SoundManager::getInstance()->playEnemyDeathSound();
}

void Enemy::notifyDeathStartEvent()
{
	if (onDeathStart)
		onDeathStart();
}

void Enemy::notifyDeathEvent()
{
	if (onDeath)
		onDeath();
}

void Enemy::initStateControllers()
{
	_idleStateController = new EnemyIdleStateController();
	_deathStateController = new EnemyDeathStateController();
	_stateControllers.insert(_stateControllers.begin(), {_idleStateController, _deathStateController});
}
