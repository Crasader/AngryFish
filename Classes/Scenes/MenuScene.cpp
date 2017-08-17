#include "MenuScene.h"
#include "Sounds/SoundManager.h"
#include "ScenesManager.h"

const std::string MenuScene::BACKGROUND_PATH = "textures/background.png";

const std::string MenuScene::BACKGROUND_PARTICLES_PATH = "particles/background_bubbles/particle_texture.plist";

const std::string MenuScene::PLAY_BUTTON_PARTICLES_PATH = "particles/button_bubbles/particle_texture.plist";

const int MenuScene::BACKGROUND_ORDER = 0;

const int MenuScene::BACKGROUND_PARTICLES_ORDER = 1;

const int MenuScene::ITEMS_ORDER = 2;

Scene * MenuScene::createScene()
{
	Scene *scene = Scene::create();
	MenuScene *sceneLayer = MenuScene::create();
	scene->addChild(sceneLayer);
	return scene;
}

bool MenuScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}
	initBackground();
	initPlayButton();
	SoundManager::getInstance()->playBackgroundMusic();
	return true;
}

void MenuScene::initPlayButton()
{
	_playButton = Label::create("Play", "fonts/Marker Felt.ttf", 48);
	this->addChild(_playButton, ITEMS_ORDER);
	_playButton->setPosition(Director::getInstance()->getWinSize() / 2.0f);

	_playButtonBubbles = ParticleSystemQuad::create(PLAY_BUTTON_PARTICLES_PATH);
	stopPlayButtonBubbles();
	this->addChild(_playButtonBubbles, ITEMS_ORDER);
	_playButtonBubbles->setPosition(_playButton->getPosition());

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		if (_playTouched == false)
		{
			_playTouched = true;
			_playButton->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f), ScaleTo::create(0.2f, 1.0f), nullptr));
			ScenesManager::getInstance()->startGameScene();
			SoundManager::getInstance()->playBubblesSound();
			splashPlayButtonBubbles();
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _playButton);
}

void MenuScene::initBackground()
{
	_backgroundSprite = Sprite::create(BACKGROUND_PATH);
	addChild(_backgroundSprite, BACKGROUND_ORDER);
	_backgroundSprite->setPosition(Director::getInstance()->getWinSize() / 2.0f);
	_backgroundSprite->setScale(1.1f);

	_backgroundBubbles = ParticleSystemQuad::create(BACKGROUND_PARTICLES_PATH);
	this->addChild(_backgroundBubbles, BACKGROUND_PARTICLES_ORDER);
	_backgroundBubbles->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, -10.0f));
	splashBackgroundBubbles();
}

void MenuScene::splashBackgroundBubbles()
{
	_backgroundBubbles->resetSystem();
}

void MenuScene::stopBackgroundBubbles()
{
	_backgroundBubbles->stopSystem();
}

void MenuScene::splashPlayButtonBubbles()
{
	_playButtonBubbles->resetSystem();
}

void MenuScene::stopPlayButtonBubbles()
{
	_playButtonBubbles->stopSystem();
}
