#pragma once
#include "PlayerStateController.h"

class PlayerDeathStateController : public PlayerStateController
{

public:
	virtual void update(float dt) override;
	virtual void executeCommand(PlayerStateCommand commandType, void *data) override;
	virtual void enter() override;
	virtual void exit() override;

};