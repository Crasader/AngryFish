#include "EnemyDeathStateController.h"

void EnemyDeathStateController::update(float dt)
{
}

void EnemyDeathStateController::executeCommand(EnemyStateCommand commandType, void *data)
{
}

void EnemyDeathStateController::enter()
{
	_enemy->playDeathSound();
	_enemy->getMainSprite()->runAction(Sequence::create(TintTo::create(0.2f, Color3B::RED), TintTo::create(0.1f, Color3B::WHITE), nullptr));
	_enemy->getMainSprite()->runAction(Sequence::create(ScaleBy::create(0.2f, 1.1f), ScaleBy::create(0.1f, 1.0f / 1.1f), nullptr));
	_enemy->getMainSprite()->runAction(Sequence::create(FadeOut::create(0.4f), CallFunc::create([&](){
		_enemy->notifyDeathEvent();
	}), nullptr));
}

void EnemyDeathStateController::exit()
{
}

EnemyState EnemyDeathStateController::getEnemyState() const
{
	return EnemyState::DEAD;
}
