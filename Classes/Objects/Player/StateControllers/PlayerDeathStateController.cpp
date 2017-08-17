#include "PlayerDeathStateController.h"

void PlayerDeathStateController::update(float dt)
{
}

void PlayerDeathStateController::executeCommand(PlayerStateCommand commandType, void *data)
{
}

void PlayerDeathStateController::enter()
{
	_player->getMainSprite()->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create([&](){
		_player->notifyDeathEvent();
	}), nullptr));
}

void PlayerDeathStateController::exit()
{
}
