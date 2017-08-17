#include "EnemyIdleStateController.h"

void EnemyIdleStateController::update(float dt)
{
	_enemy->updateRotationAndVelocity(dt);
}

void EnemyIdleStateController::executeCommand(EnemyStateCommand commandType, void *data)
{
	if (executePossibleDamageCommand(commandType, data))
		return;
}

void EnemyIdleStateController::enter()
{
}

void EnemyIdleStateController::exit()
{
}

EnemyState EnemyIdleStateController::getEnemyState() const
{
	return EnemyState::IDLE;
}
