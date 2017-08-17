#include "SoundManager.h"

SoundManager * SoundManager::getInstance()
{
	return _instance;
}

const std::string SoundManager::BACKGROUND_MUSIC_PATH = "sounds/main_music.mp3";

const std::string SoundManager::BUBBLES_SOUND_PATH = "sounds/bubbles.mp3";

void SoundManager::init()
{
	if (_instance)
	{
		delete _instance;
	}
	_instance = new SoundManager();
	_instance->prepareSounds();
}

void SoundManager::playBackgroundMusic()
{
	_musicId = AudioEngine::play2d(BACKGROUND_MUSIC_PATH, true, _volume);
}

void SoundManager::stopBackgroundMusic()
{
	if (_musicId != -1)
	{
		AudioEngine::stop(_musicId);
	}
}

void SoundManager::playBubblesSound()
{
	AudioEngine::play2d(BUBBLES_SOUND_PATH, false, _volume);
}

SoundManager * SoundManager::_instance = nullptr;

SoundManager::SoundManager()
{

}

void SoundManager::prepareSounds()
{
	AudioEngine::preload(BACKGROUND_MUSIC_PATH);
}
