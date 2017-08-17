#include "PlayerStateController.h"

void PlayerStateController::update(float dt)
{

}

void PlayerStateController::executeCommand(PlayerStateCommand commandType, void *data)
{

}

bool PlayerStateController::executePossibleDamageCommand(PlayerStateCommand commandType, void *data)
{
	if (commandType == PlayerStateCommand::DAMAGE)
	{
		_player->setDeathState();
		return true;
	}
	return false;
}

void PlayerStateController::enter()
{

}

void PlayerStateController::exit()
{

}

void PlayerStateController::setPlayer(Player *player)
{
	_player = player;
}
