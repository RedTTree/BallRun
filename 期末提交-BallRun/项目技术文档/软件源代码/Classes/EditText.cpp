#include "EditText.h"
#include "GameStart.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* EditText::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	EditText *layer = EditText::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool EditText::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto pEditBox_name = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("aboutA.png"));
	pEditBox_name->setPosition(ccp(visibleSize.width / 2, visibleSize.height * 3 / 4));
	pEditBox_name->setFontColor(Color3B(0, 0, 0));//设置字体颜色    
	pEditBox_name->setPlaceHolder("Name:");//设置预置文本    
	pEditBox_name->setMaxLength(8);//设置最大长度    
	pEditBox_name->setInputMode(EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行   
	pEditBox_name->setInputFlag(EditBox::InputFlag::INITIAL_CAPS_WORD);//设置输入标志位    
	pEditBox_name->setReturnType(EditBox::KeyboardReturnType::DONE);//设置返回类型    
	pEditBox_name->setDelegate(this);//当前类继承CCEditBoxDelegate类    
	pEditBox_name->setTag(101);
	this->addChild(pEditBox_name);

	//---------------------------------添加密码框  
	auto pEditBox_password = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("aboutA.png"));
	pEditBox_password->setPosition(ccp(visibleSize.width / 2, visibleSize.height * 2 / 4));
	pEditBox_password->setFontColor(Color3B(0, 0, 0));

	std::string str = UserDefault::sharedUserDefault()->getStringForKey("password");
	if (str.length() != 0)
	{
		const char * p = str.c_str();
		pEditBox_password->setPlaceHolder(p);
	}
	else
	{
		pEditBox_password->setPlaceHolder("password");
	}
	pEditBox_password->setMaxLength(6);
	pEditBox_password->setInputMode(EditBox::InputMode::NUMERIC);
	pEditBox_password->setInputFlag(EditBox::InputFlag::PASSWORD);
	pEditBox_password->setReturnType(EditBox::KeyboardReturnType::DONE);
	pEditBox_password->setDelegate(this);
	pEditBox_password->setTag(102);
	this->addChild(pEditBox_password);

	auto closeItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(EditText::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 1,
		origin.y + closeItem->getContentSize().height / 1));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 10);

	return true;
}

void EditText::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}
void EditText::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
}
void EditText::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
}
void EditText::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	switch (editBox->getTag())
	{
	case 101:
	//CCLOG("%s",text);
	m_name = text;
	UserDefault::sharedUserDefault()->setStringForKey("name", m_name);
		break;
	case 102:
		m_password = text;
		UserDefault::sharedUserDefault()->setStringForKey("password", m_password);
	
		break;
	default:
		break;
	}
}

void EditText::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->setDepthTest(true);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameStart::scene(), false));
}


