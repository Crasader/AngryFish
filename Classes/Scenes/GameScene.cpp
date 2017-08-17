#include "GameScene.h"
#include "Objects/Common/BaseGameObject.h"
#include "Physics/MyPhysics.h"
#include "Objects/Player/Player.h"
#include "Physics/MyCircleBody.h"
#include "ScenesManager.h"
#include "Objects/PlayerBubble/PlayerBubble.h"

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
		_player->attack();
		return true;
	};
	listener->onTouchMoved = [&](Touch *touch, Event *event)
	{
		Vec2 touchLocation = touch->getLocation();
		touchLocation = _worldLayer->convertToNodeSpace(touchLocation);
		_player->setTarget(touchLocation);
	};
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
	BodySprite *playerSprite = BodySprite::create(playerBody, Player::TEXTURE_FISH);
	playerSprite->setScale(0.2f);
	playerSprite->setSpriteName(Player::MAIN_SPRITE_NAME);
	_player->addBodySprite(playerSprite);
	playerSprite->setLocalZOrder(PLAYER_ORDER);
	_player->init();

	_player->addToWorld(_worldLayer);
	
	_player->onDeathEvent = [&]()
	{
		ScenesManager::getInstance()->startMenuScene();
	};
	_player->onShoot = [&]()
	{
		scheduleOnce([&](float dt)
		{
			createPlayerBubble();
		}, 0.02f, "CreateBubble");
	};
	addGameObject(_player);
}

void GameScene::createPlayerBubble()
{
	PlayerBubble *playerBubble = new PlayerBubble();
	MyCircleBody *bubbleBody = _physics->createCircleBody(28.0f);
	bubbleBody->setPosition(_player->getMainBody()->getPosition());
	bubbleBody->setData(playerBubble);
	bubbleBody->setAngularVelocity(RandomHelper::random_real<float>(-40.0f, 40.0f));
	float playerAngle = CC_DEGREES_TO_RADIANS(180.0f - _player->getMainBody()->getAngle() + 90.0f);
	Vec2 velocity = Vec2(cosf(playerAngle), sinf(playerAngle));
	velocity *= _player->getBubbleSpeed();
	bubbleBody->setVelocity(velocity);
	BodySprite *bubbleSprite = BodySprite::create(bubbleBody, PlayerBubble::IMAGE_PATH);
	bubbleSprite->setScale(0.2f);
	bubbleSprite->setSpriteName(PlayerBubble::MAIN_SPRITE_NAME);
	bubbleSprite->setLocalZOrder(PLAYER_ORDER);
	playerBubble->addBodySprite(bubbleSprite);
	playerBubble->init();
	playerBubble->addToWorld(_worldLayer);

	addGameObject(playerBubble);
}
