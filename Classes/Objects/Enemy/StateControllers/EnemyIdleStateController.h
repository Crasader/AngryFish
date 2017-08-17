#pragma once
#include "EnemyStateController.h"

class EnemyIdleStateController : public EnemyStateController
{
public:
	virtual void update(float dt) override;


	virtual void executeCommand(EnemyStateCommand commandType, void *data) override;


	virtual void enter() override;


	virtual void exit() override;


	virtual EnemyState getEnemyState() const override;

};