#include "MainScene.h"
#include "SelectGameScene.h"

#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}


bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//设置优先查找资源的目录
	std::vector<std::string> paths;
	paths.push_back("MainScene");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	//添加背景
	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);
	bg->setScale(0.5);
	addChild(bg);

	//添加标题
	auto title = Sprite::create("title.png");
	title->setAnchorPoint(Vec2(0.5, 0.5));
	title->setPosition(490, 300);
	title->setScale(0.5);
	addChild(title);

	//正处于播放音乐时的菜单项
	audioPlayingItem = MenuItemImage::create("AudioNormal.png", "AudioSelected.png", CC_CALLBACK_0(MainScene::playMusic, this));
	audioPlayingItem->setScale(0.5);
	audioPlayingItem->setAnchorPoint(Vec2(1, 1));
	audioPlayingItem->setPosition(visibleSize.width - 20, visibleSize.height - 20);
	audioPlayingItem->setVisible(false);

	//未播放音乐时的菜单项
	audioStopedItem = MenuItemImage::create("AudioSelected.png", "AudioNormal.png", CC_CALLBACK_0(MainScene::playMusic, this));
	audioStopedItem->setScale(0.5);
	audioStopedItem->setAnchorPoint(Vec2(1, 1));
	audioStopedItem->setPosition(visibleSize.width - 20, visibleSize.height - 20);

	//开始菜单项
	Sprite *startNormal = Sprite::create("StartNormal.png");
	Sprite *startSelected = Sprite::create("StartSelected.png");
	//startSelected->setPositionY(startNormal->getPositionY() - 20);
	auto startItem = MenuItemSprite::create(startNormal,
		startSelected,
		CC_CALLBACK_0(MainScene::startGame, this));
	startItem->setAnchorPoint(Vec2(0.5, 0.8));
	startItem->setScale(0.6);
	startItem->setPosition(visibleSize.width / 2, 180);

	//关闭菜单项
	/*Sprite *closeNormal = Sprite::create("CloseNormal.png");
	Sprite *closeSelected = Sprite::create("CloseSelected.png");*/
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_0(MainScene::closeGame, this));
	closeItem->setAnchorPoint(Vec2(0.5, 0.5));
	closeItem->setScale(0.4);
	closeItem->setPosition(visibleSize.width / 2, 50);

	//菜单
	auto menu = Menu::create(audioPlayingItem, audioStopedItem, closeItem, startItem, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(0, 0);
	this->addChild(menu);

	playMusic();

	return true;
}
//开始回调函数切换场景
void  MainScene::startGame()
{
	//auto ani = TransitionJumpZoom::create(1.0f, SelectGameScene::createScene());
	auto ani = TransitionProgressHorizontal::create(1.0f, SelectGameScene::createScene());
	Director::getInstance()->replaceScene(ani);
}
void MainScene::playMusic()
{
	isPlay = !isPlay;
	if (isPlay)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bg.mp3", true);
		audioPlayingItem->setVisible(true);
		audioStopedItem->setVisible(false);
	}
	else
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		audioPlayingItem->setVisible(false);
		audioStopedItem->setVisible(true);
	}
}

void MainScene::onExit()
{
	Layer::onExit();
	userDefault->setBoolForKey("isPlay", isPlay);
}

void MainScene::closeGame()
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}