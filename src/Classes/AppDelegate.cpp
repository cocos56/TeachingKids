#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "LearnModeScene.h"
#include "MainScene.h"
#include "LoadingScene.h"
#include "LogoScene.h"
#include "TestModeScene.h"
#include "SelectGameScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

int a = 1920 / 2, b = 1080 / 2;
static cocos2d::Size designResolutionSize = cocos2d::Size(a, b);
static cocos2d::Size smallResolutionSize = cocos2d::Size(a, b);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(a, b);
static cocos2d::Size largeResolutionSize = cocos2d::Size(a, b);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("FruitBaby", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("FruitBaby");
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	auto frameSize = glview->getFrameSize();
	// if the frame's height is larger than the height of medium size.
	if (frameSize.height > mediumResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
	}
	// if the frame's height is larger than the height of small size.
	else if (frameSize.height > smallResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	}
	// if the frame's height is smaller than the height of medium size.
	else
	{
		director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
	}

	register_all_packages();

	//设置优先查找资源的目录
	std::vector<std::string> paths;
	paths.push_back("fonts");
	paths.push_back("audio");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	// create a scene. it's an autorelease object
	//auto scene = LoadingScene::createScene();

	// run
	auto* ani = TransitionProgressHorizontal::create(1.2f, LogoScene::createScene());
	//auto ani = TransitionRotoZoom::create(1.0f, LogoScene::createScene());
	//auto ani = TransitionRotoZoom::create(1.0f, LoadingScene::createScene());
	//auto scene = TransitionRotoZoom::create(1.2f, LearnModeScene::createScene());
	//auto ani = TransitionRotoZoom::create(1.0f, MainScene::createScene());
	//auto scene = LogoScene::createScene();
	//Scene *scene = TestModeScene::createScene();

	//Scene *scene = SelectGameScene::createScene();
	//director->runWithScene(scene);
	director->runWithScene(ani);

	//预加载音效
	vector<string> fruitSpritesName = { "apple","cantaloupe","cherry","orange","watermelon" };
	string name;
	for (int i = 0; i < fruitSpritesName.size(); i++)
	{
		name = fruitSpritesName.at(i) + ".mp3";
		SimpleAudioEngine::getInstance()->preloadEffect(name.c_str());
	}

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
