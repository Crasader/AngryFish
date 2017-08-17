#pragma once
#include "../Common/BaseGameObject.h"
class EnemyStateController;
enum class EnemyStateCommand;
enum class EnemyState
{
	NONE,
	IDLE,
	DEAD
};
class Enemy : public BaseGameObject
{
public:
	static const std::string IMAGE_PATH;
	static const std::string MAIN_SPRITE_NAME;
	~Enemy();
	virtual void init() override;
	virtual void update(float dt) override;
	virtual GameObjectType getType() const override;

	BodySprite *getMainSprite() const;
	MyBody *getMainBody() const;

	EnemyState getState() const;

	void updateRotationAndVelocity(float dt);

	void setTarget(Vec2 target);

	void damage();

	void setIdleState();
	void setDeathState();
	void setCurrentStateController(EnemyStateController *stateController);
	void sendStateCommand(EnemyStateCommand commandType, void *data = nullptr);

	void playDeathSound();

	void notifyDeathStartEvent();
	void notifyDeathEvent();

	std::function<void()> onDeathStart = nullptr;
	std::function<void()> onDeath = nullptr;
private:
	void initStateControllers();
	BodySprite *_mainSprite;
	MyBody *_mainBody;
	EnemyStateController *_currentStateController = nullptr;
	EnemyStateController *_idleStateController;
	EnemyStateController *_deathStateController;
	std::vector<EnemyStateController*> _stateControllers;
	float _angularSpeed = 250.0f;
	float _movementSpeed = 60.0f;
	Vec2 _target = Vec2(0.0f, 0.0f);
};