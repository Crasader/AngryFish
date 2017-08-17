#include "GameScene.h"

cocos2d::Scene * GameScene::createScene()
{
	Scene *scene = Scene::create();
	GameScene *gameScene = GameScene::create();
	scene->addChild(gameScene);
	return scene;
}

const std::string GameScene::GAME_BACKGROUND_PATH = "textures/background.png";

const int GameScene::BACKGROUND_ORDER = 0;

bool GameScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}
	_backgroundSprite = Sprite::create(GAME_BACKGROUND_PATH);
	_backgroundSprite->setScale(1.1f);
	this->addChild(_backgroundSprite, BACKGROUND_ORDER);
	_backgroundSprite->setPosition(Director::getInstance()->getWinSize() / 2.0f);
	return true;
}
