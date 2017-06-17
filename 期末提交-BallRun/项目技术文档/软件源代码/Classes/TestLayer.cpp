#include "TestLayer.h"
#include "GameTimer.h"  
#include "Dialog.h"

CTestLayer::CTestLayer(void)
{
}


CTestLayer::~CTestLayer(void)
{
}

bool CTestLayer::init()
{
	
	if (!Layer::init())
	{
		return false;
	}


		Size visibleSize = Director::getInstance()->getVisibleSize();
	
		text2=CCLabelTTF::create("Welcome to this game!","Arial",20);
		text2->setPosition(Vec2(visibleSize.width / 2, 85));
		text2->setColor(ccc3(255,255,255));
		this->addChild(text2,1);

	/*	GameTimer * m_timer = GameTimer::createTimer(5);
		m_timer->setPosition(100, 200);
		this->addChild(m_timer);*/

		this->scheduleUpdate();


		

	return true;
}

void CTestLayer::update(float delta)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	int newX=text2->getPositionX()-1;
	if (newX<=-text2->getContentSize().width/2)
	{
		newX=visibleSize.width+text2->getContentSize().width/2;
	}
	text2->setPositionX(newX);
}

void CTestLayer::select_learn(Object* pSender){

	log("you had select this button");



	PopAlertDialog* popup = PopAlertDialog::create("background01.png", Size(800, 250));

	popup->setTitle("Message");

	popup->setContentText("This is a test message!", 20, 50, 150);

	popup->setCallBackFunc(this, callfuncN_selector(CTestLayer::popButtonCallback));

	popup->addButton("CloseNormal.png", "CloseNormal.png", "OK", 0);

	popup->addButton("CloseNormal.png", "CloseNormal.png", "Cancel", 1);

	this->addChild(popup);

}

void  CTestLayer::popButtonCallback(Node* pNode){

	log("[==========]button call back.tag %d", pNode->getTag());

	if (pNode->getTag() == 0) {

		Director::getInstance()->end();

	}

	if (pNode->getTag() == 1) {

		//pNode->getParent()->removeFromParent();

		pNode->removeFromParent();

	}



}