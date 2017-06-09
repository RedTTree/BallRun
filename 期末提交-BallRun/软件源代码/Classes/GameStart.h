//
//  GameMenuScene.h
//  example12-1
//
//  Created by shuoquan man on 12-10-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef GameStart_Scene_h
#define GameStart_Scene_h

#include "TestLayer.h"
#include "cocos2d.h"
#include "GameMark.h"
#include <algorithm>
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

USING_NS_CC;

class GameStart : public cocos2d::Layer
{
public:
	GameStart();
	~GameStart();

public:
	bool issound;
	Sprite *gameover;
	MenuItemImage* soundItem;     // 播放音乐菜单项

public:

	static cocos2d::Scene* scene();

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();
	void menuEnter();

	void BackToHelloCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(Ref* pSender);
	void GoToPersonInforCallback(Ref* pSender, Widget::TouchEventType type);
	void GoToLevelCallback(cocos2d::Ref* pSender, Widget::TouchEventType type);
	GameMark *gamemark;
	//void menuAboutCallback(cocos2d::Ref* pSender);

	//void menuSoundCallback(cocos2d::Ref* pSender);


	void onEnterTransitionDidFinish();

	void onExitTransitionDidStart();

	CREATE_FUNC(GameStart);

private:
	CTestLayer* _testlayer;
};

#endif
