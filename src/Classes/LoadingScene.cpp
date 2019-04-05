#include "LoadingScene.h"
#include "MainScene.h"

Scene*  LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool  LoadingScene::init()
{
	//先初始化父类
	if (!Layer::init())
	{
		return false;
	}

	//获取屏幕分辨率
	visibleSize = Director::getInstance()->getVisibleSize();

	//设置优先查找资源的目录
	std::vector<std::string> paths;
	paths.push_back("LoadingScene");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	//添加背景
	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setScale(0.5);
	this->addChild(bg, 0);

	//添加进度条背景精灵grassDownSprite（红色的）
	auto bg_bar = Sprite::create("red_bar.png");
	barSize = bg_bar->getContentSize();
	bg_bar->setAnchorPoint(Vec2(0, 0));
	bg_bar->setPosition((visibleSize.width - barSize.width / 2) / 2, 78);
	//创建标签
	bg_bar->setTag(0);
	bg_bar->setScale(0.5);
	this->addChild(bg_bar);

	//添加进度条（黄色的）
	bar = LoadingBar::create("orange_bar.png");
	bar->setScale(0.5);
	bar->setAnchorPoint(Vec2(0, 0));
	bar->setPosition(Vec2((visibleSize.width - barSize.width / 2) / 2, 78));
	bar->setDirection(LoadingBar::Direction::LEFT);
	this->addChild(bar, 2);

	//添加球精灵，位于的进度条上方，设置节点数为2
	ball = Sprite::create("ball.png");
	ball->setScale(0.5);
	ball->setPosition((visibleSize.width - barSize.width / 2) / 2 - ball->getContentSize().width / 8, 105);
	ball->setAnchorPoint(Vec2(0.5, 0.5));
	auto repeatforeve = RepeatForever::create(RotateBy::create(0.2, 120));
	ball->runAction(repeatforeve);
	this->addChild(ball, 2);

	//定时器；完成进度条的运行和球精灵的运动
	d = barSize.width / 2 / 100 / 4;
	schedule(schedule_selector(LoadingScene::update), 1.0 / 90);

	return true;
}
void LoadingScene::update(float f)
{
	static float count = 0;
	ball->setPositionX(ball->getPositionX() + d);

	count += 0.25;
	bar->setPercent(count);
	if (count >= 100)
	{
		unschedule(schedule_selector(LoadingScene::update));
		Director *dic = Director::getInstance();
		auto ani = TransitionProgressHorizontal::create(1.2f, MainScene::createScene());
		//auto ani = TransitionRotoZoom::create(1.0f, MainScene::createScene());
		dic->replaceScene(ani);
	}
}