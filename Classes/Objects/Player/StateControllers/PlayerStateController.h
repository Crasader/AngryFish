#pragma once
#include "../Player.h"
enum class PlayerStateCommand
{
	DAMAGE,
	ATTACK
};

class PlayerStateController
{
public:
	virtual void update(float dt);
	virtual void executeCommand(PlayerStateCommand commandType, void *data);
	virtual bool executePossibleDamageCommand(PlayerStateCommand commandType, void *data);
	virtual void enter();
	virtual void exit();
	void setPlayer(Player *player);
protected:
	Player *_player;
};