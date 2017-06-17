#include "TestScene.h"


CTestScene::CTestScene(void)
{
	_testlayer=NULL;
}


CTestScene::~CTestScene(void)
{
}


CCScene* CTestScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CTestScene *layer = CTestScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CTestScene::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		_testlayer=CTestLayer::create();
		this->addChild(_testlayer);

		bRet=true; 
	} while (0);
	return bRet;
}