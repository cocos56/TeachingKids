#pragma once

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MainScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void closeGame();
	CREATE_FUNC(MainScene);
	void startGame();
	void playMusic();
	virtual void onExit();
	UserDefault *userDefault = UserDefault::getInstance();
	bool isPlay = !userDefault->getBoolForKey("isPlay", true);

	MenuItemImage *audioPlayingItem, *audioStopedItem;
};
