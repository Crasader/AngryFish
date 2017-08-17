#pragma once
#include "PlayerStateController.h"

class PlayerAttackStateController : public PlayerStateController
{

public:
	virtual void update(float dt) override;
	virtual void executeCommand(PlayerStateCommand commandType, void *data) override;
	virtual void enter() override;
	virtual void exit() override;
private:
	bool _notifiedShoot = false;
	float _currentAttackTime = 0.0f;
	float _attackTime = 0.4f;
};