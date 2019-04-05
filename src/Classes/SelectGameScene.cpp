#include "SelectGameScene.h"
#include "MainScene.h"
#include "LearnModeScene.h"
#include "TestModeScene.h"

Scene* SelectGameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectGameScene::create();
	scene->addChild(layer);
	return scene;
}


bool SelectGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//设置优先查找资源的目录
	std::vector<std::string> paths;
	paths.push_back("SelectGameScene");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	auto sprite = Sprite::create("bg.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(0.5);
	this->addChild(sprite, 0);


	auto chapter_1 = Sprite::create("chapter1.png");
	chapter_1->setPosition(Vec2(250, 300));
	chapter_1->setScale(0.5);
	this->addChild(chapter_1, 1);

	auto chapter_2 = Sprite::create("chapter2.png");
	chapter_2->setPosition(Vec2(500, 300));
	chapter_2->setScale(0.5);
	this->addChild(chapter_2, 2);

	auto chapter_3 = Sprite::create("chapter3.png");
	chapter_3->setPosition(Vec2(750, 300));
	chapter_3->setScale(0.5);
	this->addChild(chapter_3, 3);

	auto c_1 = Sprite::create("c1.png");
	c_1->setPosition(Vec2(250, 270));
	c_1->setScale(0.45);
	this->addChild(c_1, 4);

	auto c_2 = Sprite::create("c2.png");
	c_2->setPosition(Vec2(500, 270));
	c_2->setScale(0.45);
	this->addChild(c_2, 5);

	auto c_3 = Sprite::create("c3.png");
	c_3->setPosition(Vec2(750, 270));
	c_3->setScale(0.45);
	this->addChild(c_3, 6);

	Sprite *normal, *pressed;
	normal = Sprite::create("enterNormal.png");
	pressed = Sprite::create("enterPressed.png");
	pressed->setPositionY(normal->getPositionY() - 5);

	auto en_1 = MenuItemSprite::create(normal, pressed, CC_CALLBACK_0(SelectGameScene::next1, this));
	en_1->setPosition(Vec2(250, 150));
	en_1->setScale(0.8);

	normal = Sprite::create("enterNormal.png");
	pressed = Sprite::create("enterPressed.png");
	pressed->setPositionY(normal->getPositionY() - 5);
	auto en_2 = MenuItemSprite::create(normal, pressed, CC_CALLBACK_0(SelectGameScene::next2, this));
	en_2->setPosition(Vec2(500, 150));
	en_2->setScale(0.8);

	normal = Sprite::create("enterNormal.png");
	pressed = Sprite::create("enterPressed.png");
	pressed->setPositionY(normal->getPositionY() - 5);
	auto en_3 = MenuItemSprite::create(normal, pressed, CC_CALLBACK_0(SelectGameScene::back, this));
	en_3->setPosition(Vec2(750, 150));
	en_3->setScale(0.8);

	auto m1 = Menu::create(en_1, en_2, en_3, NULL);
	m1->setPosition(0, 0);
	this->addChild(m1, 7);
	return true;
}
//进入训练
void  SelectGameScene::next1()
{
	auto ne1 = Scene::create();
	auto ayer = LearnModeScene::create();
	ne1->addChild(ayer);
	//Director::getInstance()->replaceScene(TransitionFadeDown::create(1.0f, ne1));
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.0f, ne1));
}
//进入检测
void  SelectGameScene::next2()
{
	auto ne2 = Scene::create();
	auto ayer = TestModeScene::create();
	ne2->addChild(ayer);
	//Director::getInstance()->replaceScene(TransitionFadeUp::create(1.0f, ne2));
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.2f, ne2));
}
//返回
void  SelectGameScene::back()
{
	auto bg = Scene::create();
	auto ayer = MainScene::create();
	bg->addChild(ayer);
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.0f, bg));
	//Director::getInstance()->replaceScene(TransitionFadeBL::create(1.0f, bg));
}