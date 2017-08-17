#include "GameScene.h"
#include "Objects/Common/BaseGameObject.h"
#include "Physics/MyPhysics.h"
#include "Objects/Player/Player.h"
#include "Physics/MyCircleBody.h"
#include "ScenesManager.h"
#include "Objects/PlayerBubble/PlayerBubble.h"
#include "Objects/Enemy/Enemy.h"
#include "Cocos/PerlinPositionShakeAction.h"

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
	_physics->onCollision = [&](MyBody *bodyA, MyBody *bodyB)
	{
		BaseGameObject *gameObjectA = static_cast<BaseGameObject*>(bodyA->getData());
		BaseGameObject *gameObjectB = static_cast<BaseGameObject*>(bodyB->getData());
		GameObjectType gameObjectTypeA = gameObjectA->getType();
		GameObjectType gameObjectTypeB = gameObjectB->getType();
		if (gameObjectTypeA == GameObjectType::ENEMY && gameObjectTypeB == GameObjectType::PLAYER_BUBBLE
			|| gameObjectTypeA == GameObjectType::PLAYER_BUBBLE && gameObjectTypeB == GameObjectType::ENEMY)
		{
			Enemy *enemy = nullptr;
			PlayerBubble *playerBubble = nullptr;
			if (gameObjectTypeA == GameObjectType::ENEMY)
			{
				enemy = static_cast<Enemy*>(gameObjectA);
				playerBubble = static_cast<PlayerBubble*>(gameObjectB);
			}
			else if (gameObjectTypeB == GameObjectType::ENEMY)
			{
				enemy = static_cast<Enemy*>(gameObjectB);
				playerBubble = static_cast<PlayerBubble*>(gameObjectA);
			}
			if (playerBubble->getState() == PlayerBubbleState::FLY && enemy->getState() == EnemyState::IDLE)
			{
				playerBubble->setDeath();
				enemy->damage();
			}
		}
		if (gameObjectTypeA == GameObjectType::ENEMY && gameObjectTypeB == GameObjectType::PLAYER
			|| gameObjectTypeA == GameObjectType::PLAYER && gameObjectTypeB == GameObjectType::ENEMY)
		{
			Enemy *enemy = nullptr;
			Player *player = nullptr;
			if (gameObjectTypeA == GameObjectType::ENEMY)
			{
				enemy = static_cast<Enemy*>(gameObjectA);
				player = static_cast<Player*>(gameObjectB);
			}
			else if (gameObjectTypeB == GameObjectType::ENEMY)
			{
				enemy = static_cast<Enemy*>(gameObjectB);
				player = static_cast<Player*>(gameObjectA);
			}
			if (enemy->getState() == EnemyState::IDLE)
			{
				player->damage();
			}
		}

	};
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
		checkTouchOnEnemies(touchLocation);
		return true;
	};
	listener->onTouchMoved = [&](Touch *touch, Event *event)
	{
		Vec2 touchLocation = touch->getLocation();
		touchLocation = _worldLayer->convertToNodeSpace(touchLocation);
		_player->setTarget(touchLocation);
		checkTouchOnEnemies(touchLocation);
	};
	//listener->onTouchEnded = CC_CALLBACK_2(onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, _worldLayer);

	this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(5.0f), CallFunc::create([&](){
		int randNum = RandomHelper::random_int(0, 3);
		for (int i = 0; i < randNum; i++)
		{
			createEnemyAtRandomPlace();
		}
	}), nullptr)));
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

void GameScene::createEnemyAtRandomPlace()
{
	float minDistanceToPlayer = 400.0f;
	float maxDistanceToPlayer = 900.0f;
	float angle = CC_DEGREES_TO_RADIANS(RandomHelper::random_real<float>(0.0f, 360.0f));
	Vec2 enemyPosition = _player->getMainBody()->getPosition() + Vec2(sinf(angle), cosf(angle)) * RandomHelper::random_real<float>(minDistanceToPlayer, maxDistanceToPlayer);
	float enemyRotation = RandomHelper::random_real<float>(0.0f, 360.0f);
	createEnemy(enemyPosition, enemyRotation);
}

void GameScene::createEnemy(Vec2 position, float angle)
{
	Enemy *enemy = new Enemy();
	MyCircleBody *playerBody = _physics->createCircleBody(40.0f);
	playerBody->setPosition(position);
	playerBody->setAngle(angle);
	playerBody->setData(enemy);
	BodySprite *enemySprite = BodySprite::create(playerBody, Enemy::IMAGE_PATH);
	enemySprite->setScale(0.2f);
	enemySprite->setSpriteName(Enemy::MAIN_SPRITE_NAME);
	enemy->addBodySprite(enemySprite);
	enemySprite->setLocalZOrder(PLAYER_ORDER);
	enemy->init();
	enemy->setTarget(_player->getMainBody()->getPosition());
	enemy->addToWorld(_worldLayer);

	enemy->onDeathStart = [&]()
	{
		_backgroundSprite->runAction(Sequence::create(TintTo::create(0.2f, Color3B(255, 240, 240)), TintTo::create(0.1f, Color3B::WHITE), nullptr));
		_backgroundSprite->runAction(Sequence::create(ScaleBy::create(0.2f, 1.01f), ScaleBy::create(0.1f, 1.0f/1.01f), nullptr));
	};
	enemy->onDeath = [&]()
	{
	};
	addGameObject(enemy);
	_enemies.push_back(enemy);
}

void GameScene::checkTouchOnEnemies(Vec2 touchLocation)
{
	for (auto &enemy : _enemies)
	{
		if (enemy->getState() == EnemyState::IDLE)
		{
			Rect rect = enemy->getMainSprite()->getBoundingBox();
			if (rect.containsPoint(touchLocation))
			{
				_player->attack();
			}
		}
	}
}
