#include "PlayerIdleStateController.h"
#include "../Player.h"

void PlayerIdleStateController::update(float dt)
{
	_player->updateRotation(dt);
}

void PlayerIdleStateController::executeCommand(PlayerStateCommand commandType, void *data)
{
	if (executePossibleDamageCommand(commandType, data))
		return;
	if (commandType == PlayerStateCommand::ATTACK)
	{
		_player->tryToAttack();
	}
}

void PlayerIdleStateController::enter()
{
	_player->setIdleAnimation();
}

void PlayerIdleStateController::exit()
{
}
