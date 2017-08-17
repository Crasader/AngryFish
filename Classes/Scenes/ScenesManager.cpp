#include "ScenesManager.h"
#include "cocos2d.h"
#include "MenuScene.h"
#include "GameScene.h"
using namespace cocos2d;

ScenesManager * ScenesManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ScenesManager();
	}
	return _instance;
}

void ScenesManager::startMenuScene()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MenuScene::createScene()));
}

void ScenesManager::startGameScene()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
}

ScenesManager * ScenesManager::_instance = nullptr;
