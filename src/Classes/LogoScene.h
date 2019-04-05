#pragma once

#include "cocos2d.h"

class LogoScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(LogoScene);

	//进入游戏资源加载界面
	void EnterLoadingScene();
};
