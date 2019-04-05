#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
using namespace std;

class TestModeScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	void initFruitItems();
	void initFruitItem(int i);
	void initRandomNumbers();

	void playAudio();
	void check(Ref *r, int n);
	void right();
	void wrong();
	void back();
	void showScore();
	virtual void onExit();

	LabelTTF *label=nullptr;
	Size visibleSize;
	static string _Name;
	vector<Menu*> fruitMenus;
	vector<string> fruitSpritesName = { "apple","cantaloupe","cherry","orange","watermelon" };
	vector<int> randomNumbers;

	UserDefault *userDefault = UserDefault::getInstance();
	int score = userDefault->getIntegerForKey("score", 0);

	CREATE_FUNC(TestModeScene);
};