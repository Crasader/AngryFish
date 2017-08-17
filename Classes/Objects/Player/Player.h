#pragma once
#include "../Common/BaseGameObject.h"
#include "Physics/MyBody.h"

class PlayerStateController;
enum class PlayerStateCommand;
class Player : public BaseGameObject
{
public:
	static const std::string MAIN_SPRITE_NAME;
	static const std::string TEXTURE_FISH;
	static const std::string TEXTURE_FISH_ATTACK;
	~Player();
	virtual void init() override;
	virtual void update(float dt) override;

	void updateRotation(float dt);

	virtual GameObjectType getType() const override;

	void setTarget(Vec2 target);

	BodySprite *getMainSprite() const;
	MyBody *getMainBody() const;
	float getBubbleSpeed() const;

	void attack();

	void setCurrentStateController(PlayerStateController *stateController);
	void sendStateCommand(PlayerStateCommand commandType, void *data = nullptr);

	void tryToAttack();
	void setAttackState();
	void setIdleState();
	void setDeathState();

	void setIdleAnimation();
	void setAttackAnimation();

	void resetCurrentReloadTime();
	
	void playAttackSound();

	void notifyDeathEvent();
	void notifyShootEvent();

	std::function<void()> onDeathEvent = nullptr;
	std::function<void()> onShoot = nullptr;
private:
	void initStateControllers();
	BodySprite *_mainSprite;
	MyBody *_mainBody;
	float _angularSpeed = 250.0f;
	Vec2 _target = Vec2(0.0f, 0.0f);
	Texture2D *_idleTexture;
	Texture2D *_attackTexture;
	float _currentReloadTime = 0.0f;
	float _reloadTime = 0.5f;
	float _bubbleSpeed = 145.0f;
	PlayerStateController *_currentStateController = nullptr;
	PlayerStateController *_idleStateController;
	PlayerStateController *_attackStateController;
	PlayerStateController *_deathStateController;
	std::vector<PlayerStateController*> _stateControllers;
};