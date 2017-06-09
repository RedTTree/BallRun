#ifndef __macstudycocos2dx__PopAlertDialog__

#define __macstudycocos2dx__PopAlertDialog__



#pragma once

#include "cocos2d.h"

#include "cocos-ext.h"





USING_NS_CC;

USING_NS_CC_EXT;





class PopAlertDialog :public LayerColor{  //�̳�LayerColor�࣬�������layer����ɫ��͸����

public:

	PopAlertDialog();

	~PopAlertDialog();



	virtual bool init();

	CREATE_FUNC(PopAlertDialog);



	static PopAlertDialog* create(const char* backgroudImage, Size dialogSize);



	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchMoved(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);



	void setTitle(const char* title, int fontsize = 20);



	void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddingTop = 50);



	void setCallBackFunc(Ref* target, SEL_CallFuncN callfun);



	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);



	virtual void onEnter();

	virtual void onExit();



	void backgroundFinish();



private:

	void buttonCallBack(Ref* pSender);



	int m_contentPadding;

	int m_contentPaddingTop;

	Size m_dialogContentSize; //�Ի����С



	Ref* m_callbackListener;

	SEL_CallFuncN m_callback;



	CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);

	CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);

	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);

	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);

	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);

};





#endif /* defined(__macstudycocos2dx__PopAlertDialog__) */