//
//  GameMenuScene.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-13.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
//

#include "GameStart.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PersonInfor.h"
#include "t.h"
#include "EditText.h"

using namespace CocosDenshion;

GameStart::GameStart(){

}
GameStart::~GameStart(){

}

Scene* GameStart::scene()
{
	auto scene = CCScene::create();
	auto layer = GameStart::create();
	scene->addChild(layer);

	return scene;
}
bool GameStart::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// ��ȡ��ʾ�����С����ʾԭ��λ��
	Size size = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// ����ͼƬ
	auto spriteBackground = Sprite::create("start.png");
	spriteBackground->setScale(1);
	spriteBackground->setPosition(Point(size.width / 2 + origin.x, size.height / 2 + origin.y));
	this->addChild(spriteBackground, 0, 0);

	if (1){
		auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(GameStart::menuCloseCallback, this));
		closeItem->setPosition(Vec2(origin.x + size.width - closeItem->getContentSize().width / 1-30,
			origin.y + closeItem->getContentSize().height / 1));

/*
		auto enter = Button::create("level.png", "level.png", "level.png");
		enter->addTouchEventListener(CC_CALLBACK_2(GameStart::GoToPersonInforCallback, this));
		enter->setScale(0.8);
		enter->setPosition(cocos2d::Vec2(300, 500));
		enter->setEnabled(true);
		this->addChild(enter);
		
		auto enter2 = Button::create("personalInfor.png", "personalInfor.png", "personalInfor.png");
		enter2->addTouchEventListener(CC_CALLBACK_2(GameStart::GoToLevelCallback, this));
		enter2->setScale(0.8);
		enter2->setPosition(Point(300, 200));
		enter2->setEnabled(true);
		this->addChild(enter2);
		*/
		auto btnRetry = Button::create("level.png", "level.png", "level.png");
		btnRetry->addTouchEventListener(CC_CALLBACK_2(GameStart::GoToPersonInforCallback, this));
		btnRetry->setScale(0.7);
		btnRetry->setPosition(cocos2d::Vec2(500, 200));
		this->addChild(btnRetry);
		btnRetry->setPressedActionEnabled(true);
		auto btnNext = Button::create("personalInfor.png", "personalInfor.png", "personalInfor.png");
		btnNext->setScale(0.8);
		btnNext->addTouchEventListener(CC_CALLBACK_2(GameStart::GoToLevelCallback, this));
		btnNext->setPosition(cocos2d::Vec2(500, 400));
		this->addChild(btnNext);
		//1

		//δͨ����ʾ
		gameover = CCSprite::create("gameover.png");
		gameover->setAnchorPoint(Point(0.5, 0.5));
		gameover->setPosition(Point(0, 0));
		gameover->setPosition(Point(size.width / 2, size.height / 2 + 70));
		gameover->setVisible(false);
		//gameover->setScale(0.5);
		addChild(gameover, 5);

		// ���ذ�ť
		auto back = MenuItemImage::create("back.png",
			"back.png",
			CC_CALLBACK_1(GameStart::BackToHelloCallback, this));
		back->setPosition(Point(origin.x + 40, origin.y + 85));
		back->setScale(0.62);

		Menu* pMenu = CCMenu::create(back, NULL);
		pMenu->setPosition(Point::ZERO);
		this->addChild(pMenu, 5, 25);


		//pMenu->setVisible(false);
		//pMenu->setEnabled(false);



		//if��Ϸ����
		//Menu* pMenu = (Menu *)this->getChildByTag(25);
	/*	pMenu->setVisible(true);
		pMenu->setEnabled(true);

		gameover->setVisible(true);
		gameover->setScale(0);

		pMenu->setScale(0);
		pMenu->runAction(ScaleTo::create(0.5, 1));

		gameover->runAction(ScaleTo::create(0.5, 0.5));
		//����*/

		//1







	/*	gamemark = new GameMark();
		addChild(gamemark, 4);*/

		_testlayer = CTestLayer::create();
		this->addChild(_testlayer);
	}

	// --------------------------------------------------
	// ��Ӳ˵���ť��Ĭ��Ϊ��ֹ��Ӧ������������������������Ӧ����

	

	return true;
}

// ���볡��ʱ����
void GameStart::onEnter(){
	Layer::onEnter();

	// �볡��������ʾ�˵���С���Ķ���
	/*Node* mainmenu = (Node*)this->getChildByTag(3);
	mainmenu->setScale(0.5);
	mainmenu->runAction(Sequence::create(ScaleTo::create(0.5, 1),
		CallFunc::create(CC_CALLBACK_0(GameStart::menuEnter, this)),
		nullptr));*/

}

void GameStart::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	// ȡ��OpenGL����Ȳ���
	Director::getInstance()->setDepthTest(false);
}

void GameStart::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

// �˳�����ʱ����
void GameStart::onExit(){
	Layer::onExit();
}


// �رղ˵���Ӧ����
void GameStart::menuCloseCallback(Ref* pSender)
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

void GameStart::BackToHelloCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->setDepthTest(true);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, HelloWorld::scene(), false));
}

void GameStart::GoToPersonInforCallback(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	Director::getInstance()->setDepthTest(true);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, EditText::scene(), false));
}

void GameStart::GoToLevelCallback(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	Director::getInstance()->setDepthTest(true);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, Test::createScene(), false));
	//Director::getInstance()->replaceScene(t::create(0.5, cscene(), false));
}
