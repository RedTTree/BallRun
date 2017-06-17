#include "AppDelegate.h"
#include "PersonInfor.h"
#include "GameStart.h"
#include "HelloWorldScene.h"
#include "PersonInfor.h"
#include "t.h"
#include "TestScene.h"
#include "EditText.h"
#include "mainSence.h"
#include "gameSence.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}



static void keyEventCallback(EventKeyboard::KeyCode code, Event *event);

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLView::create("My Game");
		glview = GLView::createWithRect("My Game", Rect(0, 0, 1136, 640));
        director->setOpenGLView(glview);
    }
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	FileUtils::getInstance()->addSearchPath("res");
    // create a scene. it's an autorelease object
	//auto scene = CTestScene::scene();
	//auto scene = GameStart::scene();
	//auto scene = EditText::scene();
	auto scene = HelloWorld::scene();
	//auto scene = mainSence::createScene();
	//auto scene = Test::createScene();/*¹Ø¿¨Ñ¡Ôñ*/
	//auto scene = cscene();
    // run
   director->runWithScene(scene);

	//runTextFiledTTFManager();



	EventListenerKeyboard *listener = EventListenerKeyboard::create();
	listener->onKeyReleased = keyEventCallback;
	director->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

static void keyEventCallback(EventKeyboard::KeyCode code, Event *event)
{
	typedef EventKeyboard::KeyCode KeyCode;
	switch (code)
	{
	case KeyCode::KEY_BACKSPACE:
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
#else
		Director::getInstance()->end();
#endif
		break;
	case KeyCode::KEY_DELETE:
		IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
		break;
	}
}