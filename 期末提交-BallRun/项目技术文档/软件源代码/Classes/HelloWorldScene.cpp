#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "GameStart.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	Size size = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// ±³¾°Í¼Æ¬
	auto spriteBackground = Sprite::create("firstScene.jpg");
	spriteBackground->setScale(0.5);
	spriteBackground->setPosition(Point(size.width / 2 + origin.x, size.height / 2 + origin.y));
	this->addChild(spriteBackground, 0, 0);

	if (1){
		auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
		closeItem->setPosition(Vec2(origin.x + size.width - closeItem->getContentSize().width / 1,
			origin.y + closeItem->getContentSize().height / 1));

		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 10);
	}


	auto enter = MenuItemImage::create("enter.png",
		"enter.png",
		CC_CALLBACK_1(HelloWorld::menuNewGameCallback, this));
	enter->setScale(0.6);
	enter->setPosition(Point(origin.x + size.width / 2, origin.y + size.height / 2 - enter->getContentSize().height * 0.25));
	enter->setEnabled(true);


	// ÉùÒô²Ëµ¥Ïî
	soundItem = CCMenuItemImage::create("sound-on-A.png",
		"sound-on-B.png",
		CC_CALLBACK_1(HelloWorld::menuSoundCallback, this));
	//soundItem->setScale(0.5);
	soundItem->setEnabled(true);
	soundItem->setPosition(Point(origin.x + 40, origin.y + 40));

	auto menu = Menu::create(enter, soundItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1, 3);

	// ³õÊ¼»¯ÉùÒôÏà¹Ø
	issound = true;
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	//  if(0){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
	// }
	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void HelloWorld::menuNewGameCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->setDepthTest(true);
	m_soundID = SimpleAudioEngine::sharedEngine()->playEffect("Button10.wav");
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameStart::scene(), false));
}

// ¿ØÖÆÊÇ·ñ¾²Òô
void HelloWorld::menuSoundCallback(cocos2d::Ref* pSender)
{
	//ÉèÖÃÉùÒô
	if (!issound){
		soundItem->setNormalImage(Sprite::create("sound-on-A.png"));
		soundItem->setDisabledImage(Sprite::create("sound-on-B.png"));

		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
		issound = true;
	}
	else{
		soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
		soundItem->setDisabledImage(CCSprite::create("sound-off-B.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		issound = false;
	}
}