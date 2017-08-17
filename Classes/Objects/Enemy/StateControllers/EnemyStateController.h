#pragma once
#include "../Enemy.h"
enum class EnemyStateCommand
{
	DAMAGE
};
class EnemyStateController
{
public:
	virtual void update(float dt);
	virtual void executeCommand(EnemyStateCommand commandType, void *data);
	virtual bool executePossibleDamageCommand(EnemyStateCommand commandType, void *data);
	virtual void enter();
	virtual void exit();
	void setEnemy(Enemy *enemy);
	virtual EnemyState getEnemyState() const;
protected:
	Enemy *_enemy;
};