#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class BaseGameObject;
class Player;
class Enemy;
class MyPhysics;
class GameScene : public Layer
{
public:
	static Scene *createScene();
	CREATE_FUNC(GameScene);
	static const std::string GAME_BACKGROUND_PATH;
	static const int BACKGROUND_ORDER;
	static const int PLAYER_ORDER;
	~GameScene();
	virtual bool init() override;

	void update(float delta);

	void addGameObject(BaseGameObject *gameObject);
	
	void initPlayer();

	void createPlayerBubble();

	void createEnemyAtRandomPlace();
	void createEnemy(Vec2 position, float angle); 
private:
	Layer *_worldLayer;
	Sprite *_backgroundSprite;
	std::vector<BaseGameObject*> _gameObjects;
	std::vector<Enemy*> _enemies;
	MyPhysics *_physics;
	Player *_player;
	void checkTouchOnEnemies(Vec2 touchLocation);
};