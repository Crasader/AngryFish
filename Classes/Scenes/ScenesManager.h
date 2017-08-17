#pragma once

class ScenesManager
{
public:
	static ScenesManager *getInstance();

	void startMenuScene();
	void startGameScene();

private:
	static ScenesManager *_instance;
};