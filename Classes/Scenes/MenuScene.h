#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;
class MenuScene : public Layer
{
public:
	static const std::string BACKGROUND_PATH;
	static const std::string BACKGROUND_PARTICLES_PATH;
	static const std::string PLAY_BUTTON_PARTICLES_PATH;
	static const int BACKGROUND_ORDER;
	static const int BACKGROUND_PARTICLES_ORDER;
	static const int ITEMS_ORDER;
	static Scene *createScene();
	CREATE_FUNC(MenuScene);
	virtual bool init() override;

	void initPlayButton();

	void initBackground();

	void splashBackgroundBubbles();
	void stopBackgroundBubbles();

	void splashPlayButtonBubbles();
	void stopPlayButtonBubbles();
private:
	Sprite *_backgroundSprite;
	ParticleSystemQuad *_backgroundBubbles;
	ParticleSystemQuad *_playButtonBubbles;
	Label *_playButton;
	bool _playTouched = false;
};