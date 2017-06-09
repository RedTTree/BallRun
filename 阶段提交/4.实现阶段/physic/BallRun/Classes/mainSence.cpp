#include "mainSence.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* mainSence::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	Vect gravity(0.0f, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity);
	//scene->getPhysicsWorld()->setSpeed(80);//设置速度
	// 'layer' is an autorelease object
	auto layer = mainSence::create();

	layer->setPhyWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool mainSence::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	 m_timer = GameTimer::createTimer(300);
	m_timer->setPosition(1030.77, 561.85);
	
	this->addChild(m_timer);

	auto btnRetry = Button::create("button1.png", "button1.png", "button1.png");
	btnRetry->addTouchEventListener(CC_CALLBACK_2(mainSence::btnRetryed, this));
	btnRetry->setPosition(cocos2d::Vec2(1032.16,50.34));
	this->addChild(btnRetry);
	btnRetry->setPressedActionEnabled(true);
	auto btnBack = Button::create("button3.png", "button3.png", "button3.png");
	btnBack->addTouchEventListener(CC_CALLBACK_2(mainSence::btnBacked, this));
	btnBack->setPosition(cocos2d::Vec2(104.78, 50.34));
	this->addChild(btnBack);
	btnBack->setPressedActionEnabled(true);


	Point verts1[] = {
		Point(61.59, 442.52),
		Point(56.03, 206.17),
		Point(352.15, 29.6),
		Point(783.14, 29.6),
		Point(1091.78, 206.17),
		Point(1097.33, 438.33),
		Point(799.80, 616.28),
		Point(366.03, 616.28)
	};
	edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgePolygon(verts1, 8);
	edgeSp->setPosition(Point(0, 0));
	boundBody->getShape(0)->setRestitution(1.0f);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setDensity(0.0f);
	edgeSp->setPhysicsBody(boundBody);
	this->addChild(edgeSp);
	edgeSp->setTag(0);

paddle = Sprite::create("bg.png");	
paddle->setScale(1);
paddle->setAnchorPoint(ccp(0, 0.5));
paddle->setPosition(Point(0, visibleSize.height / 2));
this->addChild(paddle,-1);

auto lab1 = Sprite::create("tiao.png");
lab1->setAnchorPoint(ccp(0.5, 0.5));
lab1->setPosition(Point(639.52, 379.8));
auto labBody = PhysicsBody::createBox(lab1->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
labBody->getShape(0)->setRestitution(1.0f);
labBody->getShape(0)->setFriction(0.0f);
labBody->getShape(0)->setDensity(10.0f);
labBody->setRotationEnable(true);
labBody->setRotationOffset(130);
labBody->setDynamic(false);
lab1->setPhysicsBody(labBody);
this->addChild(lab1);

auto lab2 = Sprite::create("tiao.png");
lab2->setAnchorPoint(ccp(0.5, 0.5));
lab2->setPosition(Point(490, 249.98));

auto labBody2 = PhysicsBody::createBox(lab2->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
labBody2->getShape(0)->setRestitution(1.0f);
labBody2->getShape(0)->setFriction(0.0f);
labBody2->getShape(0)->setDensity(10.0f);
labBody2->setRotationEnable(true);
labBody2->setRotationOffset(130);
labBody2->setDynamic(false);
lab2->setPhysicsBody(labBody2);
this->addChild(lab2);


auto mball = Sprite::create("Ball.png", Rect(0, 0, 52, 52));
mball->setPosition(visibleSize.width / 2 , 320);
auto mballBody = PhysicsBody::createCircle(mball->getContentSize().width / 2.);
mballBody->getShape(0)->setRestitution(1.0f);
mballBody->getShape(0)->setFriction(0.0f);
mballBody->getShape(0)->setDensity(10.0f);
mballBody->setDynamic(false);
mballBody->setContactTestBitmask(0xFFFFFFFF);
mball->setPhysicsBody(mballBody);
mball->setTag(22);
this->addChild(mball);

	ball = Sprite::create("Ball.png", Rect(0, 0, 52, 52));
	ball->setPosition(212.67, 489.32);
	ball->setAnchorPoint(ccp(0.5, 0.5));
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2.);
	ballBody->getShape(0)->setRestitution(1.0f);
	ballBody->getShape(0)->setFriction(0.0f);
	ballBody->getShape(0)->setDensity(1.0f);
	ballBody->setGravityEnable(false);
//	Vect force = Vect(0.0f, -100.0f);
	//ballBody->applyImpulse(force);
	ballBody->setContactTestBitmask(0xFFFFFFFF);
	ballBody->setVelocity(Vec2(0, -400));
	
	
	ball->setPhysicsBody(ballBody);
	ball->setTag(1);
	this->addChild(ball);
	preball_point = ball->getPosition();
	m_streak = CCMotionStreak::create(.5, 10, 40, Color3B::RED, "Ball.png");
	m_streak->setPosition(ccp(visibleSize.width / 2 - 350, 500));
	this->addChild(m_streak, -1);
	CCActionInterval *colorAction = CCRepeatForever::create((CCActionInterval *)CCSequence::create(
		CCTintTo::create(0.1f, 255, 0, 0),
		CCTintTo::create(0.1f, 0, 255, 0),
		CCTintTo::create(0.1f, 0, 0, 255),
		CCTintTo::create(0.f, 0, 255, 255),
		CCTintTo::create(0.1f, 255, 255, 0),
		CCTintTo::create(0.1f, 255, 0, 255),
		CCTintTo::create(0.1f, 255, 255, 255),
		NULL)); 
	m_streak->runAction(colorAction);

	setTouchEnabled(true);
	this->schedule(schedule_selector(mainSence::tick), 0);
	this->scheduleUpdate();
	return true;
}

void mainSence::tick(float dt)
{
	if (succe == 0){
		auto gameOverScene = GameOverScene::create();
		char* mtime = new char[10];
		int pTime = 3000 - (int)m_timer->gettime();
		int number = (int)m_timer->gettime() / 3;
		sprintf(mtime, "WIN!!LEF:%d : %d---SCORE:%d", (int)m_timer->gettime() / 60, (int)m_timer->gettime() % 60, (int)number);
		log(mtime);
		gameOverScene->getLayer()->getLabel()->setString(mtime);
		Director::getInstance()->replaceScene(gameOverScene);
	}
}

void mainSence::onEnter()
{
	Layer::onEnter();
	
	auto touch_listener = EventListenerTouchOneByOne::create();
	auto contactListener = EventListenerPhysicsContact::create();
	touch_listener->setSwallowTouches(true);
	touch_listener->onTouchBegan = CC_CALLBACK_2(mainSence::onTouchBegan, this);
	touch_listener->onTouchMoved = CC_CALLBACK_2(mainSence::onTouchMoved, this);
	touch_listener->onTouchEnded = CC_CALLBACK_2(mainSence::onTouchEnded, this);
	touch_listener->onTouchCancelled = CC_CALLBACK_2(mainSence::onTouchCancelled, this);
	contactListener->onContactBegin = CC_CALLBACK_1(mainSence::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//contactListener->onContactBegin = CC_CALLBACK_1(mainSence::onContactBegin, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);

}
bool mainSence::onContactBegin(cocos2d::PhysicsContact& contact){
	auto body_1 = (Sprite*)contact.getShapeA()->getBody()->getNode(); //发生碰撞的物体1
	auto body_2 = (Sprite*)contact.getShapeB()->getBody()->getNode(); //发生碰撞的物体2
	log("contact");
	if (body_1->getTag() == 22)
	{
		body_1->removeFromParent();
		succe = 0;
		return true;
	}
	if (body_2->getTag() == 22)
	{
		body_2->removeFromParent();
		succe = 0;
		return true;
	}
	if (body_1->getTag() == 1000){
		body_1->removeFromParent();
		poi = 0;
	}
	if (body_2->getTag() == 1000){
		body_2->removeFromParent();
		poi = 0;
	}
	return true;
}

void mainSence::btnRetryed(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		log("touch ended");
		Director::getInstance()->replaceScene(mainSence::createScene());
	}
}

void mainSence::btnBacked(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		log("touch ended");
		Director::getInstance()->replaceScene(mainSence::createScene());
	}
}

bool mainSence::onTouchBegan(Touch *touch, Event *unused_event){
	Point location = touch->getLocation();
	pre_point = cur_point = location;
	return true;
}


void mainSence::onTouchCancelled(Touch *touch, Event *unused_event){

	return;
}

void mainSence::onTouchMoved(Touch *touch, Event *unused_event){

}
void mainSence::onTouchEnded(Touch *touch, Event *unused_event){
	/*
	auto node = getChildByTag(1000);
	if (node ){
		log("node");
		node->removeAllChildren();
		node->removeFromParent();
		auto line = getChildByTag(1000);
		if (line){
			log("line");
			line->setVisible(false);
		}
	}*/
	poi = 1;
	Point location = touch->getLocation();
	cur_point = location;
	
}
void mainSence::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){

	DrawPrimitives::setDrawColor4B(0, 255, 255, 255);
	glLineWidth(8);
	if (poi == 1){
		auto lineBody = PhysicsBody::createEdgeSegment(pre_point, cur_point);
		auto edgeNode = Node::create();
		edgeNode->setTag(1000);
		lineBody->getShape(0)->setRestitution(1.0f);
		lineBody->getShape(0)->setFriction(0.0f);
		lineBody->getShape(0)->setDensity(10.0f);
		lineBody->setDynamic(false);
		lineBody->setContactTestBitmask(0xFFFFFFFF);
		edgeNode->setPhysicsBody(lineBody);
		addChild(edgeNode);
		DrawPrimitives::drawLine(pre_point, cur_point);
		poi =1;
	}
}
void mainSence::update(float dt)
{  

	if (ball && succe ==1)
	{
curball_point = ball->getPosition();
	auto hei = curball_point.y - preball_point.y;

	if ((preball_point - curball_point).getLength() <.5){
		log("no!!!!!!!");

		ball->removeFromParent();
		ball = Sprite::create("Ball.png", Rect(0, 0, 52, 52));
		ball->setPosition(curball_point);
		auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2.);
		ballBody->getShape(0)->setRestitution(1.0f);
		ballBody->getShape(0)->setFriction(0.0f);
		ballBody->getShape(0)->setDensity(1.0f);
		ballBody->setGravityEnable(false);
		ballBody->setContactTestBitmask(0xFFFFFFFF);
		if (hei>0)
		{
			ballBody->setVelocity(Vec2(300, 300));
		}
		else
		{
			ballBody->setVelocity(Vec2(-300, -300));
		}

		ball->setPhysicsBody(ballBody);
		ball->setTag(1);
		this->addChild(ball);
	}
	preball_point = curball_point;
	m_streak->setPosition(ball->getPosition());
	}
	if (poi == 0){
		auto node = getChildByTag(1000);
		if (node){
			log("node");
			node->removeAllChildren();
			node->removeFromParent();
			auto line = getChildByTag(1000);

		}
	}


}

