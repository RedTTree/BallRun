#ifndef LevelScene_h  
#define LevelScene_h  

#include "cocos-ext.h"  
#include "cocos2d.h"  

using namespace cocos2d::extension;
using namespace cocos2d;

class LevelScene : public Layer
{
public:

	bool init();

	CREATE_FUNC(LevelScene);

	//以下是注册触摸事件和实现各种的touch函数  
	virtual bool TouchBegan(Touch * touch, Event * pEvent);
	virtual void TouchMoved(Touch * touch, Event * pEvent);
	virtual void TouchEnded(Touch * touch, Event * pEvent);
	virtual void TouchCancelled(Touch *touch, Event * event);

	//最后这个函数来校验每个关卡的位置，是各个关卡都位于屏幕的中央  
	void adjustScrollView(float offset);

private:
	//将CCScrollView作为自己的层添加进来  
	cocos2d::extension::ScrollView * m_scrollView;

	//触摸点的位置  
	Point m_touchPoint;

	//CCScrollView的便宜量  
	Point m_offsetPoint;

	//当前为第几个关卡  
	int m_nCurPage;
};

#endif /* LevelScene_h */