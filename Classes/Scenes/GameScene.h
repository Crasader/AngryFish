#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public Layer
{
public:
	static Scene *createScene();
	CREATE_FUNC(GameScene);
	static const std::string GAME_BACKGROUND_PATH;
	static const int BACKGROUND_ORDER;
	virtual bool init() override;

private:
	Sprite *_backgroundSprite;
};