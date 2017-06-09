#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CTestLayer :
	public CCLayer
{
public:
	CTestLayer(void);
	~CTestLayer(void);

	CREATE_FUNC(CTestLayer);
	virtual bool init();

	virtual void update(float delta);
	virtual void select_learn(Object* pSender);
	virtual void popButtonCallback(Node* pNode);
	CCLabelTTF* text1;
	CCLabelTTF* text2;
};

