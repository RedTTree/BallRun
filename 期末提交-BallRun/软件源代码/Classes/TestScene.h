#pragma once
#include "cocos2d.h"
#include "TestLayer.h"

USING_NS_CC;

class CTestScene :
	public CCScene
{
public:
	CTestScene(void);
	~CTestScene(void);

	CREATE_FUNC(CTestScene);
	static cocos2d::CCScene* scene();
	virtual bool init();
private:
	CTestLayer* _testlayer;
};

