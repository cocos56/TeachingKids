#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;

class LoadingScene :public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(LoadingScene);
	void update(float f);
	Sprite *ball;
	Size visibleSize, barSize;
	float d;
	LoadingBar *bar;
	void enterScene();
};

