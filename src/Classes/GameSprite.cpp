#include "GameSprite.h"

GameSprite::GameSprite() {}
GameSprite::~GameSprite()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

//初始化静态变量
char _spriteFileName[20] = { 0 };
char _spriteAudioName[20] = { 0 };
static std::string _Name;
GameSprite *pSprite;
Size windowSize;

GameSprite* GameSprite::createFruitSprite(int i)
{
	std::vector<Sprite*> _sprites;
	std::vector<std::string> _spriteNames = { "apple","cantaloupe","cherry","orange","watermelon"};

	_Name = _spriteNames.at(i);
	sprintf(_spriteFileName, "%s.png", _spriteNames.at(i).c_str());
	sprintf(_spriteAudioName, "%s.mp3", _spriteNames.at(i).c_str());

	pSprite = new GameSprite();

	if (pSprite->initWithFile(_spriteFileName))
	{
		//设置当前对象为自动释放对象
		pSprite->autorelease();
		//添加标签，比如“apple”
		pSprite->addLable();
		//添加单点触摸事件
		pSprite->addEvents();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void GameSprite::addLable()
{
	LabelTTF *label = LabelTTF::create(_Name, "Felt.ttf", 80);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setPosition(pSprite->getContentSize().width / 2, pSprite->getContentSize().height+30);
	label->setColor(Color3B(247, 181, 33));
	this->addChild(label);
}

void GameSprite::addEvents()
{
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event)->bool
	{
		Vec2 p = touch->getLocation();
		Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			return true;
		}
		return false;
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		Vec2 p = touch->getLocation();
		GameSprite::touchEvent(touch, p);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void GameSprite::touchEvent(Touch* touch, cocos2d::Vec2 _p)
{
	SimpleAudioEngine::getInstance()->playEffect(_spriteAudioName);
	touchEffect();
}

void GameSprite::touchEffect()
{
	auto scaleUP = ScaleBy::create(0.0625f, 1.25 / 2);
	auto scaleDown = ScaleTo::create(0.0625f, 1.0 / 2);
	auto rotLeft = RotateBy::create(0.0625f, -40.0f);
	auto rotRight = RotateBy::create(0.0625f, 40.0f);
	auto rotFix = RotateTo::create(0.001, 0.0f);

	auto seq = Sequence::create(scaleUP, rotLeft, scaleDown, rotRight, scaleUP, rotRight, scaleDown, rotLeft, rotFix, NULL);
	this->runAction(seq);

}

void GameSprite::removeMySprite()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	listener->release();
	removeFromParentAndCleanup(true);
}