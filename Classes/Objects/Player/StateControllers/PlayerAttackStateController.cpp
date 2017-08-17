#include "PlayerAttackStateController.h"

void PlayerAttackStateController::update(float dt)
{
	_player->updateRotation(dt);
	_currentAttackTime += dt;
	if (_currentAttackTime >= _attackTime / 2.0f && !_notifiedShoot)
	{
		_notifiedShoot = true;
		_player->playAttackSound();
		_player->notifyShootEvent();
	}
	if (_currentAttackTime >= _attackTime)
	{
		_player->setIdleState();
	}
}

void PlayerAttackStateController::executeCommand(PlayerStateCommand commandType, void *data)
{
	if (executePossibleDamageCommand(commandType, data))
		return;
}

void PlayerAttackStateController::enter()
{
	_currentAttackTime = 0.0f;
	_notifiedShoot = false;
	_player->setAttackAnimation();
}

void PlayerAttackStateController::exit()
{
}
