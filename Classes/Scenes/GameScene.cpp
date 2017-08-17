#include "GameScene.h"
#include "Objects/Common/BaseGameObject.h"
#include "Physics/MyPhysics.h"
#include "Objects/Player/Player.h"
#include "Physics/MyCircleBody.h"

cocos2d::Scene * GameScene::createScene()
{
	Scene *scene = Scene::create();
	GameScene *gameScene = GameScene::create();
	scene->addChild(gameScene);
	return scene;
}

const std::string GameScene::GAME_BACKGROUND_PATH = "textures/background.png";

const int GameScene::BACKGROUND_ORDER = 0;

const int GameScene::PLAYER_ORDER = 1;

GameScene::~GameScene()
{
	delete _physics;
}

bool GameScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}
	_worldLayer = Layer::create();
	this->addChild(_worldLayer);
	_backgroundSprite = Sprite::create(GAME_BACKGROUND_PATH);
	_backgroundSprite->setScale(1.1f);
	_worldLayer->addChild(_backgroundSprite, BACKGROUND_ORDER);
	_backgroundSprite->setPosition(Director::getInstance()->getWinSize() / 2.0f);

	_physics = new MyPhysics();
	scheduleUpdate();
	initPlayer();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		Vec2 touchLocation = touch->getLocation(); 
		touchLocation = _worldLayer->convertToNodeSpace(touchLocation);
		_player->setTarget(touchLocation);
		return true;
	};
	//listener->onTouchMoved = CC_CALLBACK_2(onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, _worldLayer);
	return true;
}

void GameScene::update(float delta)
{
	_physics->update(delta);
	for (auto &gameObject : _gameObjects)
	{
		gameObject->update(delta);
	}
}

void GameScene::addGameObject(BaseGameObject *gameObject)
{
	_gameObjects.push_back(gameObject);
}

void GameScene::initPlayer()
{
	_player = new Player();
	MyCircleBody *playerBody = _physics->createCircleBody(40.0f);
	playerBody->setPosition(Director::getInstance()->getWinSize() / 2.0f);
	playerBody->setData(_player);
	BodySprite *playerSprite = BodySprite::create(playerBody, "textures/fish.png");
	playerSprite->setScale(0.2f);
	playerSprite->setSpriteName(Player::MAIN_SPRITE_NAME);
	_player->addBodySprite(playerSprite);
	playerSprite->setLocalZOrder(PLAYER_ORDER);
	_player->init();

	_player->addToWorld(_worldLayer);

	addGameObject(_player);
}
