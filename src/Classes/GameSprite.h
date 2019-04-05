#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class GameSprite : public Sprite
{
public:
	GameSprite();
	~GameSprite();
	static GameSprite* createFruitSprite(int i);

	void addLable();
	void addEvents();

	void touchEvent(Touch* touch, Vec2 _p);
	void removeMySprite();
	void touchEffect();

	EventListenerTouchOneByOne* listener;
};