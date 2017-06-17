#include "LevelScene.h"  
#include "EditText.h"
#include "mainSence.h"
#include <math.h> //用到了fabs()函数，用来求绝对值的  

bool LevelScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		Size winSize = Director::getInstance()->getWinSize();
		
		//ScrollView继承自Layer,传入的参数是view size的大小  
		//view size也就是人看到的大小，content size也就是内容的大小  
		//这里设置为整个屏幕的大小，也就是我们通过设备的整个屏幕去看里边的内容  
		cocos2d::extension::ScrollView * scrollView = cocos2d::extension::ScrollView::create(Size(winSize.width, winSize.height));

		//***********方式1:我觉得挺好的****************/  

		//        //以下是ScrollView的一些常用函数  
		//        //设置是否有反弹的效果，反弹就是当超出scrollview的大小的时候回到原来的位置  
		//        scrollView->setBounceable(true);  
		//          
		//        //        ScrollView默认锚点是在(0,0)处  
		//        scrollView->ignoreAnchorPointForPosition(false);  
		//        scrollView->setPosition(Point(winSize.width/2, winSize.height/2));  
		//        //设置滑动方向  
		//        scrollView->setDirection(ScrollView::Direction::HORIZONTAL);  
		//          
		//  

		//公共：创建一个Layer，将内容添加到Layer中，然后将这个layer添加到scrollview中  
		Layer * layer = Layer::create();
		for (int i = 0; i<2; i++)
		{
			String * string = String::createWithFormat("%d.png", i + 1);
			Sprite * sprite = Sprite::create(string->getCString());
				sprite->setScale(0.45);
		
			//将所有的精灵都放到屏幕的中间显示  
			sprite->setPosition(Point(winSize.width *0.4, winSize.height / 4) + Point(winSize.width*i, 0));
			sprite->setContentSize(Size(400, 400));
			sprite->setTag(i + 1);
			layer->addChild(sprite);
		}
		//设置scrollView中的内容，必须先设置内容再设置内容的大小  
		scrollView->setContainer(layer);
		scrollView->setContentSize(Size(winSize.width * 2, winSize.height));

		//***********方式2:屏蔽scrollView这个层的触摸，采用其他的实现方法****************/  

		//屏蔽scrollView这个层的触摸，采用其他的实现方法  
		scrollView->setTouchEnabled(false);
		//设置里边内容的偏移量  
		scrollView->setContentOffset(Point(0, 0));
		this->addChild(scrollView);

		m_scrollView = scrollView;
		this->m_nCurPage = 0;

		bRet = true;

		//让本层来接受触摸事件!!!!!!!!!!!!!!!!!!!!  
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(LevelScene::TouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(LevelScene::TouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(LevelScene::TouchEnded, this);
		touchListener->onTouchCancelled = CC_CALLBACK_2(LevelScene::TouchCancelled, this);
		touchListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	} while (0);

	return bRet;
}


bool LevelScene::TouchBegan(Touch * touch, Event * pEvent)
{
	//用开始的触摸点和scroll的偏移量初始化以下的成员变量  
	this->m_touchPoint = touch->getLocation();
	this->m_offsetPoint = this->m_scrollView->getContentOffset();
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//	Rect rect = Rect(winSize.width / 2, winSize.height / 2, 500, 500);
	Rect rect = Rect(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y, 800, 800);
	
	bool isClicked = rect.containsPoint(m_touchPoint);
	/* 点击范围判断 */
	if (isClicked)
	{
		Director::getInstance()->setDepthTest(true);
		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, mainSence::createScene(), false));
	}
	

	//以下的这一点特别要注意，大家可以先注释掉以下的这句话然后运行程序，会发现如果触摸不是很快  
	//的时候不会有什么问题，但是如果触摸进行的很快，关卡的位置偏移的就不会正确，以下的代码正是解决这个问题到  
	if ((int)this->m_offsetPoint.x % ((int)Director::getInstance()->getWinSize().width) == 0)
	{
		return true;
	}
	
	return false;
}


/*以下代码的整体含义就是当手指移动的时候，让关卡跟随手指移动，当移动结束的时候，判断结束点和开始
触摸点的位置，对关卡的位置做相应的处理*/

//设置关卡跟随手指的方向移动  
void LevelScene::TouchMoved(Touch * touch, Event * pEvent)
{
	Point point = touch->getLocation();
	Point direction = point - this->m_touchPoint;

	//Point spriteDirection = ccpAdd(this->m_offsetPoint,direction);  
	//只在x方向偏移  
	Point spriteDirection = Point(direction.x + this->m_offsetPoint.x, 0);
	this->m_scrollView->setContentOffset(spriteDirection);
}

//以下的代码是重点，当结束触摸的时候，为了使关卡显示在屏幕的中间，我们需要这么做  
void LevelScene::TouchEnded(Touch * touch, Event * pEvent)
{
	Point endPoint = touch->getLocation();
	float distance = endPoint.x - this->m_touchPoint.x;
	//手指移动的距离小于20的时候，就将偏移量作为0处理  
	if (fabs(distance) < 20)
	{
		this->adjustScrollView(0);
	}
	else
	{
		//将偏移量作为参数传进来  
		this->adjustScrollView(distance);
	}
}

//以下的代码是重点，当结束触摸的时候，为了使关卡显示在屏幕的中间，我们需要这么做  
void LevelScene::TouchCancelled(Touch * touch, Event * pEvent)
{

}

//调整关卡的最终位置  
void LevelScene::adjustScrollView(float offset)
{
	Size winSize = Director::getInstance()->getWinSize();
	// 我们根据 offset 的实际情况来判断移动效果  
	//如果手指往左划，offset大于0，说明页面在减小，往右增大  
	if (offset < 0)
		m_nCurPage++;
	else if (offset > 0)
		m_nCurPage--;

	//不允许超出最左边的一页和最右边的一页  
	if (m_nCurPage < 0)
		m_nCurPage = 0;
	else if (m_nCurPage > 4)
		m_nCurPage = 4;

	Point adjustPoint = Point(-winSize.width * m_nCurPage, 0);
	//这个函数比setContentOffset多了一个参数，第二个参数是设置时间的，就是用多长的时间来改变偏移量  
	this->m_scrollView->setContentOffsetInDuration(adjustPoint, 0.3f);
}