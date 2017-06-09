#include "PersonInfor.h"
#include "VisibleRect.h"

#define FONT_NAME "fonts/Marker Felt.ttf"
#define FONT_SIZE 36

static Rect getRect(Node* node){
	Rect rect;
	rect.origin = node->getPosition();
	rect.size = node->getContentSize();
	rect.origin.x -= rect.size.width / 2;
	rect.origin.y -= rect.size.height / 2;
	return rect;
}

void runTextFiledTTFManager(){




	auto scene = Scene::create();

	TextFiledTTFTest* layer = new TextFiledTTFTest();
	layer->autorelease();  //交给内存池进行管理

	scene->addChild(layer);

	Director::getInstance()->runWithScene(scene);

}

CCScene* cscene()
{
	auto scene = Scene::create();

	TextFiledTTFTest* layer = new TextFiledTTFTest();
	layer->autorelease();  //交给内存池进行管理

	scene->addChild(layer);

	// return the scene
	return scene;
}

keyBoradNotificationLayer::keyBoradNotificationLayer() :_trackNode(0){
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(keyBoradNotificationLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(keyBoradNotificationLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool keyBoradNotificationLayer::onTouchBegan(Touch* touch, Event* event){

	_beganPos = convertToNodeSpace(touch->getLocation());

	return true;
}

void keyBoradNotificationLayer::onTouchEnded(Touch *touch, Event *event){

	if (!_trackNode){
		return;
	}

	auto _endPos = touch->getLocation();

	//做了个判断,滑动差距大于5的话则代表不会被触发输入法  
	float distance = 5.0f;
	if (abs(_endPos.x - _beganPos.x) > distance ||
		abs(_endPos.y - _beganPos.y) > distance){

		//抹掉首次触摸的值
		_beganPos.x = _beganPos.y = -1;

		return;
	}
	/*如果点击的区域是在此文本框上就打开输入法*/
	Rect rect;

	auto touchPoint = convertTouchToNodeSpaceAR(touch);

	log("KeyboardNotificationLayer:clickedAt(%f,%f)", touchPoint.x, touchPoint.y);

	rect = getRect(_trackNode);

	log("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
		rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

	this->onClickTrackNode(rect.containsPoint(touchPoint));
}

void keyBoradNotificationLayer::keyboardWillShow(IMEKeyboardNotificationInfo& info){

	Rect rect = getRect(_trackNode);

	log(" jin ");

	//_trackNode和键盘的交集监测
	if (!rect.intersectsRect(info.end)){
		return;
	}
	//计算软键盘需要的高度
	float adjustHeight = info.end.getMaxY() - rect.getMinY();

	/*调整所有的子节点*/
	auto& children = getChildren();
	Node * node = 0;
	ssize_t count = children.size();
	Vec2 pos;
	for (int i = 0; i < count; ++i)
	{
		node = children.at(i);
		pos = node->getPosition();
		pos.y += adjustHeight;
		node->setPosition(pos);
	}

}

void TextFiledTTFTest::onClickTrackNode(bool b){
	auto mTextFiled = (TextFieldTTF*)_trackNode;

	if (b){
		mTextFiled->attachWithIME();
	}
	else{
		mTextFiled->detachWithIME();
	}
}

void TextFiledTTFTest::onEnter(){
	keyBoradNotificationLayer::onEnter();  //必须先调用父类的onEnter方法
	Size size = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	
	auto loginItem = MenuItemImage::create("aboutA.png",
		"aboutA.png",
		CC_CALLBACK_1(TextFiledTTFTest::menuCloseCallback, this));
	//loginItem->setScale(0.5);
	loginItem->setPosition(Point(origin.x + size.width / 2, origin.y + size.height / 2 + loginItem->getContentSize().height * 4));
	loginItem->setEnabled(true);

	auto menu = Menu::create(loginItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1, 3);

	//KEY_ENTER

	auto s = Director::getInstance()->getWinSize();

	auto mTextFiled = TextFieldTTF::textFieldWithPlaceHolder("click here for input", FONT_NAME, FONT_SIZE);

	mTextFiled->setPosition(VisibleRect::center());

	addChild(mTextFiled);

	_trackNode = mTextFiled;
}



void TextFiledTTFTest::menuCloseCallback(Ref* pSender)
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