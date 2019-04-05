#pragma once

#include "cocos2d.h"
USING_NS_CC;

class SelectGameScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectGameScene);
	void next1();
	void next2();
	void back();
};

