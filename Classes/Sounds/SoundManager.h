#pragma once
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d;
using namespace cocos2d::experimental;
class SoundManager
{
public:
	static SoundManager *getInstance();
	static const std::string BACKGROUND_MUSIC_PATH;
	static const std::string BUBBLES_SOUND_PATH;
	static const std::string BUBBLES_ATTACK_1_SOUND_PATH;
	static const std::string BUBBLES_ATTACK_2_SOUND_PATH;
	static void init();

	void playBackgroundMusic();
	void stopBackgroundMusic();

	void playBubblesSound();
	void playBubbleAttackSound();
private:
	static SoundManager *_instance;
	SoundManager();
	void prepareSounds();
	int _musicId = -1;
	float _volume = 1.0f;
};