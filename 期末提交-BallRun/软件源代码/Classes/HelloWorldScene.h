#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class HelloWorld :public cocos2d::CCLayer, public cocos2d::CCTextFieldDelegate
{
public:
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();
	bool issound;
	MenuItemImage* soundItem;
	int m_soundID;
	// there's no 'id' in cpp, so we recommend to return the class instance pointer
	static cocos2d::CCScene* scene();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuNewGameCallback(cocos2d::Ref* pSender);

	void menuSoundCallback(cocos2d::Ref* pSender);

	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__