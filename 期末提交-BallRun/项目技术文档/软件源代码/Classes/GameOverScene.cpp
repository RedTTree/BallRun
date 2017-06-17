#include "GameOverScene.h"
#include "gameSence.h"
#include "mainSence.h"


USING_NS_CC;


bool GameOverScene::init()
{
	if( Scene::init() )
	{
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

GameOverScene::~GameOverScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

bool GameOverLayer::init()
{
	if ( LayerColor::initWithColor( Color4B(255,255,255,255) ) )
	{
		auto winSize = Director::getInstance()->getWinSize();
		this->_label = LabelTTF::create("","Artial", 32);
		_label->retain();
		_label->setColor( Color3B(0, 0, 0) );
		_label->setPosition( Point(winSize.width/2, winSize.height/2) );
		this->addChild(_label);

		auto btnRetry = Button::create("button1.png", "button1.png", "button1.png");
		btnRetry->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::btnRetryed, this));
		btnRetry->setPosition(cocos2d::Vec2(104.78, 45.34));
		this->addChild(btnRetry);
		btnRetry->setPressedActionEnabled(true);
		auto btnNext = Button::create("button2.png", "button2.png", "button2.png");
		btnNext->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::btnNexted, this));
		btnNext->setPosition(cocos2d::Vec2(1032.16, 45.34));
		this->addChild(btnNext);
		btnNext->setPressedActionEnabled(true);
		
		this->runAction( Sequence::create(
                                          DelayTime::create(30),
                                          CallFunc::create(CC_CALLBACK_0(GameOverLayer::gameOverDone, this)),
                                          NULL));
		
        return true;
	}
	else
	{
		return false;
	}
}

void GameOverLayer::btnRetryed(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		log("touch ended");
		Director::getInstance()->replaceScene(mainSence::createScene());
	}
}

void GameOverLayer::btnNexted(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		log("touch ended");
		Director::getInstance()->replaceScene(gameSence::createScene());
	}
}

void GameOverLayer::gameOverDone()
{
	Director::getInstance()->replaceScene(gameSence::createScene());
}

GameOverLayer::~GameOverLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}