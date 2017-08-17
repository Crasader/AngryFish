#include "EnemyStateController.h"

void EnemyStateController::update(float dt)
{

}

void EnemyStateController::executeCommand(EnemyStateCommand commandType, void *data)
{

}

bool EnemyStateController::executePossibleDamageCommand(EnemyStateCommand commandType, void *data)
{
	if (commandType == EnemyStateCommand::DAMAGE)
	{
		_enemy->notifyDeathStartEvent();
		_enemy->setDeathState();
		return true;
	}
	return false;
}

void EnemyStateController::enter()
{

}

void EnemyStateController::exit()
{

}

void EnemyStateController::setEnemy(Enemy *enemy)
{
	_enemy = enemy;
}

EnemyState EnemyStateController::getEnemyState() const
{
	return EnemyState::NONE;
}
