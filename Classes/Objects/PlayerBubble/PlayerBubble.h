#pragma once
#include "../Common/BaseGameObject.h"
enum class PlayerBubbleState
{
	FLY,
	DEATH
};
class PlayerBubble : public BaseGameObject
{
public:
	static const std::string IMAGE_PATH;
	static const std::string MAIN_SPRITE_NAME;
	virtual void init() override;
	virtual void update(float dt) override;
	virtual GameObjectType getType() const override;
	void setFly();
	void setDeath();

	void notifyDeathEvent();

	std::function<void()> onDeath = nullptr;
private:
	BodySprite *_mainSprite;
	PlayerBubbleState _state;
};