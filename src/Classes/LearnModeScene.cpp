#include "LearnModeScene.h"
#include "SelectGameScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* LearnModeScene::createScene()
{
	Scene *scene = Scene::create();
	LearnModeScene *layer = LearnModeScene::create();
	scene->addChild(layer);
	return scene;
}

bool LearnModeScene::init()
{
	if (Layer::init())
	{
		//获取分辨率（窗口大小）
		windowSize = getContentSize();

		//设置优先查找资源的目录
		std::vector<std::string> paths;
		paths.push_back("fruit");
		paths.push_back("audio");
		FileUtils::getInstance()->setSearchResolutionsOrder(paths);

		//添加背景
		Sprite *bg = Sprite::create("bg.png");
		bg->setAnchorPoint(Vec2(0, 0));
		bg->setScale(0.5);
		addChild(bg);

		//设置返回菜单项（菜单与菜单项的区别：一个菜单包含很多菜单项，菜单项只有添加到菜单里面才能正常显示）
		Sprite *back_normal = Sprite::create("back.png");
		Sprite *back_pressed = Sprite::create("back_pressed.png");
		MenuItemSprite *backItem = MenuItemSprite::create(back_normal, back_pressed, CC_CALLBACK_0(LearnModeScene::backAction, this));
		backItem->setScale(0.5);
		backItem->setAnchorPoint(Vec2(0, 1));
		backItem->setPosition(0, windowSize.height);

		//设置右键菜单项
		Sprite *right_normal = Sprite::create("right.png");
		float x = (windowSize.width - right_normal->getContentSize().width)/2;
		Sprite *right_pressed = Sprite::create("right_pressed.png");
		rightItem = MenuItemSprite::create(right_normal, right_pressed, CC_CALLBACK_0(LearnModeScene::rightAction, this));
		rightItem->setAnchorPoint(Vec2(0.5, 0.5));
		rightItem->setPosition(x+right_normal->getContentSize().width + 35, windowSize.height / 2);
		rightItem->setScale(0.5);

		//设置左键菜单项
		Sprite *left_normal = Sprite::create("left.png");
		Sprite *left_pressed = Sprite::create("left_pressed.png");
		leftItem = MenuItemSprite::create(left_normal, left_pressed, CC_CALLBACK_0(LearnModeScene::leftAction, this));
		leftItem->setAnchorPoint(Vec2(0.5, 0.5));
		leftItem->setPosition(x-35, windowSize.height / 2);
		leftItem->setScale(0.5);

		//设置菜单（把所有菜单项加到菜单里），并挂载到父节点上
		Menu *menu = Menu::create(backItem, rightItem, leftItem, NULL);
		menu->setAnchorPoint(Vec2(0, 0));
		menu->setPosition(0, 0);
		addChild(menu);

		//添加水果精灵
		addFruitSprite();
		return true;
	}
	return false;
}

void LearnModeScene::backAction()
{
	//auto ani = TransitionJumpZoom::create(1.0f, SelectGameScene::createScene());
	auto ani = TransitionProgressHorizontal::create(1.0f, SelectGameScene::createScene());
	Director::getInstance()->replaceScene(ani);
}

void LearnModeScene::rightAction()
{
	++fruitNum;
	addFruitSprite();
}

void LearnModeScene::leftAction()
{
	--fruitNum;
	addFruitSprite();
}

void LearnModeScene::showArrow()
{
	if (fruitNum == 0)
	{
		leftItem->setVisible(false);
	}
	else
	{
		leftItem->setVisible(true);
	}

	if (fruitNum == 4)
	{
		rightItem->setVisible(false);
	}
	else
	{
		rightItem->setVisible(true);
	}
}

void LearnModeScene::addFruitSprite()
{
	if (fruitSprite != nullptr)
	{
		fruitSprite->removeFromParent();
	}
	fruitSprite = GameSprite::createFruitSprite(fruitNum);
	windowSize = getContentSize();
	fruitSprite->setScale(0.5);
	fruitSprite->setAnchorPoint(Vec2(0.5, 0.5));
	fruitSprite->setPosition(windowSize.width/2, windowSize.height / 2);
	addChild(fruitSprite);
	showArrow();
}