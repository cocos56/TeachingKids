#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "GameSprite.h"

class LearnModeScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void backAction();
	void rightAction();
	void leftAction();
	void showArrow();
	void addFruitSprite();

	EventListenerTouchOneByOne* listener;
	GameSprite* fruitSprite=nullptr;
	Size windowSize;
	int fruitNum = 0;
	MenuItemSprite *rightItem, *leftItem;

	CREATE_FUNC(LearnModeScene);
};