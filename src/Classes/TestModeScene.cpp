#include "TestModeScene.h"
#include "SelectGameScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* TestModeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TestModeScene::create();
	scene->addChild(layer);
	return scene;
}

bool TestModeScene::init()
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
	paths.push_back("TestModeScene");
	paths.push_back("audio");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	//添加背景
	Sprite *bg = Sprite::create("bg.png");
	bg->setScale(0.5);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);
	addChild(bg);

	//添加返回菜单项
	Sprite *back_normal = Sprite::create("back.png");
	Sprite *back_pressed = Sprite::create("back_pressed.png");
	back_pressed->setPositionY(back_normal->getPositionY() - 10);
	MenuItemSprite *backItem = MenuItemSprite::create(back_normal, back_pressed, CC_CALLBACK_0(TestModeScene::back, this));
	backItem->setScale(0.5);
	backItem->setAnchorPoint(Vec2(0, 1));
	backItem->setPosition(0, visibleSize.height);

	//设置菜单（把所有菜单项加到菜单里），并添加
	Menu *menu = Menu::create(backItem, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(0, 0);
	addChild(menu);

	//添加分数背景
	Sprite *score_bg = Sprite::create("score_bg.png");
	score_bg->setScale(0.5);
	score_bg->setAnchorPoint(Vec2(1, 1));
	score_bg->setPosition(visibleSize.width, visibleSize.height);
	addChild(score_bg);

	//添加分数
	showScore();

	//添加选择提示
	Sprite *select = Sprite::create("select.png");
	select->setScale(0.5);
	select->setAnchorPoint(Vec2(0.5, 1));
	select->setPosition(visibleSize.width / 2, visibleSize.height);
	addChild(select);

	//初始化水果精灵
	initFruitItems();

	//初始化随机数
	initRandomNumbers();

	//随机播放音频
	playAudio();


	return true;
}

void TestModeScene::initFruitItems()
{
	for (int i = 0; i < fruitSpritesName.size(); i++)
	{
		initFruitItem(i);
	}
}

void TestModeScene::initFruitItem(int i)
{
	string photoName = fruitSpritesName.at(i) + ".png";
	Sprite *fruitSprite = Sprite::create(photoName);
	fruitSprite->setScale(0.5);
	fruitSprite->setAnchorPoint(Vec2(0, 0));
	Sprite *fruitSpritePressed = Sprite::create(photoName);
	fruitSpritePressed->setScale(0.6);
	fruitSpritePressed->setAnchorPoint(Vec2(0, 0));

	MenuItemSprite* fruitItem = MenuItemSprite::create(fruitSprite, fruitSpritePressed, CC_CALLBACK_1(TestModeScene::check, this, i));
	fruitItem->setAnchorPoint(Vec2(0, 0));
	static float x = (visibleSize.width - fruitSpritesName.size()*(fruitSprite->getContentSize().width / 2 - 30)) / 2;
	fruitItem->setPosition(x + i * (fruitSprite->getContentSize().width / 2 - 30), 100 + (i % 2) * fruitSprite->getContentSize().height / 2);
	auto m = Menu::create(fruitItem, NULL);
	m->setAnchorPoint(Vec2(0, 0));
	m->setPosition(0, 0);
	addChild(m);
	fruitMenus.push_back(m);
}

void TestModeScene::check(Ref *r, int n)
{
	if (n == randomNumbers.back())
	{
		fruitMenus.at(n)->removeFromParent();
		randomNumbers.pop_back();
		right();
		//CCLOG("right");
	}
	else
	{
		wrong();
		//CCLOG("wrong");
	}
	showScore();
}

void TestModeScene::right()
{
	score += 10;
	playAudio();
	SimpleAudioEngine::getInstance()->playEffect("right.mp3");
}

void TestModeScene::wrong()
{
	score -= 5;
	SimpleAudioEngine::getInstance()->playEffect("wrong.mp3");
}

void TestModeScene::playAudio()
{
	if (!randomNumbers.empty())
	{
		string audioName = fruitSpritesName.at(randomNumbers.back()) + ".mp3";
		SimpleAudioEngine::getInstance()->playEffect(audioName.c_str());
	}
}

void TestModeScene::initRandomNumbers()
{
	int i, size = fruitSpritesName.size();
	for (i = 0; i < size; i++)
	{
		randomNumbers.push_back(i);
	}

	srand(time(NULL));
	for (i = 1; i < size; i++)
	{
		swap(randomNumbers.at(i), randomNumbers.at(rand() % i));//随机交换
	}
}

void TestModeScene::back()
{
	//auto ani = TransitionJumpZoom::create(1.0f, SelectGameScene::createScene());
	auto ani = TransitionProgressHorizontal::create(1.0f, SelectGameScene::createScene());
	Director::getInstance()->replaceScene(ani);
}

void TestModeScene::showScore()
{
	if (label != nullptr)
	{
		label->removeFromParent();
	}
	label = LabelTTF::create(to_string(score), "Felt.ttf", 36);
	label->setAnchorPoint(Vec2(1, 1));
	label->setPosition(visibleSize.width - 10, visibleSize.height - 5);
	label->setColor(Color3B(148, 204, 179));
	addChild(label);
}

void TestModeScene::onExit()
{
	Layer::onExit();
	userDefault->setIntegerForKey("score", score);
}