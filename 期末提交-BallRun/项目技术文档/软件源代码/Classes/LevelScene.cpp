#include "LevelScene.h"  
#include "EditText.h"
#include "mainSence.h"
#include <math.h> //�õ���fabs()���������������ֵ��  

bool LevelScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		Size winSize = Director::getInstance()->getWinSize();
		
		//ScrollView�̳���Layer,����Ĳ�����view size�Ĵ�С  
		//view sizeҲ�����˿����Ĵ�С��content sizeҲ�������ݵĴ�С  
		//��������Ϊ������Ļ�Ĵ�С��Ҳ��������ͨ���豸��������Ļȥ����ߵ�����  
		cocos2d::extension::ScrollView * scrollView = cocos2d::extension::ScrollView::create(Size(winSize.width, winSize.height));

		//***********��ʽ1:�Ҿ���ͦ�õ�****************/  

		//        //������ScrollView��һЩ���ú���  
		//        //�����Ƿ��з�����Ч�����������ǵ�����scrollview�Ĵ�С��ʱ��ص�ԭ����λ��  
		//        scrollView->setBounceable(true);  
		//          
		//        //        ScrollViewĬ��ê������(0,0)��  
		//        scrollView->ignoreAnchorPointForPosition(false);  
		//        scrollView->setPosition(Point(winSize.width/2, winSize.height/2));  
		//        //���û�������  
		//        scrollView->setDirection(ScrollView::Direction::HORIZONTAL);  
		//          
		//  

		//����������һ��Layer����������ӵ�Layer�У�Ȼ�����layer��ӵ�scrollview��  
		Layer * layer = Layer::create();
		for (int i = 0; i<2; i++)
		{
			String * string = String::createWithFormat("%d.png", i + 1);
			Sprite * sprite = Sprite::create(string->getCString());
				sprite->setScale(0.45);
		
			//�����еľ��鶼�ŵ���Ļ���м���ʾ  
			sprite->setPosition(Point(winSize.width *0.4, winSize.height / 4) + Point(winSize.width*i, 0));
			sprite->setContentSize(Size(400, 400));
			sprite->setTag(i + 1);
			layer->addChild(sprite);
		}
		//����scrollView�е����ݣ������������������������ݵĴ�С  
		scrollView->setContainer(layer);
		scrollView->setContentSize(Size(winSize.width * 2, winSize.height));

		//***********��ʽ2:����scrollView�����Ĵ���������������ʵ�ַ���****************/  

		//����scrollView�����Ĵ���������������ʵ�ַ���  
		scrollView->setTouchEnabled(false);
		//����������ݵ�ƫ����  
		scrollView->setContentOffset(Point(0, 0));
		this->addChild(scrollView);

		m_scrollView = scrollView;
		this->m_nCurPage = 0;

		bRet = true;

		//�ñ��������ܴ����¼�!!!!!!!!!!!!!!!!!!!!  
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
	//�ÿ�ʼ�Ĵ������scroll��ƫ������ʼ�����µĳ�Ա����  
	this->m_touchPoint = touch->getLocation();
	this->m_offsetPoint = this->m_scrollView->getContentOffset();
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//	Rect rect = Rect(winSize.width / 2, winSize.height / 2, 500, 500);
	Rect rect = Rect(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y, 800, 800);
	
	bool isClicked = rect.containsPoint(m_touchPoint);
	/* �����Χ�ж� */
	if (isClicked)
	{
		Director::getInstance()->setDepthTest(true);
		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, mainSence::createScene(), false));
	}
	

	//���µ���һ���ر�Ҫע�⣬��ҿ�����ע�͵����µ���仰Ȼ�����г��򣬻ᷢ������������Ǻܿ�  
	//��ʱ�򲻻���ʲô���⣬��������������еĺܿ죬�ؿ���λ��ƫ�ƵľͲ�����ȷ�����µĴ������ǽ��������⵽  
	if ((int)this->m_offsetPoint.x % ((int)Director::getInstance()->getWinSize().width) == 0)
	{
		return true;
	}
	
	return false;
}


/*���´�������庬����ǵ���ָ�ƶ���ʱ���ùؿ�������ָ�ƶ������ƶ�������ʱ���жϽ�����Ϳ�ʼ
�������λ�ã��Թؿ���λ������Ӧ�Ĵ���*/

//���ùؿ�������ָ�ķ����ƶ�  
void LevelScene::TouchMoved(Touch * touch, Event * pEvent)
{
	Point point = touch->getLocation();
	Point direction = point - this->m_touchPoint;

	//Point spriteDirection = ccpAdd(this->m_offsetPoint,direction);  
	//ֻ��x����ƫ��  
	Point spriteDirection = Point(direction.x + this->m_offsetPoint.x, 0);
	this->m_scrollView->setContentOffset(spriteDirection);
}

//���µĴ������ص㣬������������ʱ��Ϊ��ʹ�ؿ���ʾ����Ļ���м䣬������Ҫ��ô��  
void LevelScene::TouchEnded(Touch * touch, Event * pEvent)
{
	Point endPoint = touch->getLocation();
	float distance = endPoint.x - this->m_touchPoint.x;
	//��ָ�ƶ��ľ���С��20��ʱ�򣬾ͽ�ƫ������Ϊ0����  
	if (fabs(distance) < 20)
	{
		this->adjustScrollView(0);
	}
	else
	{
		//��ƫ������Ϊ����������  
		this->adjustScrollView(distance);
	}
}

//���µĴ������ص㣬������������ʱ��Ϊ��ʹ�ؿ���ʾ����Ļ���м䣬������Ҫ��ô��  
void LevelScene::TouchCancelled(Touch * touch, Event * pEvent)
{

}

//�����ؿ�������λ��  
void LevelScene::adjustScrollView(float offset)
{
	Size winSize = Director::getInstance()->getWinSize();
	// ���Ǹ��� offset ��ʵ��������ж��ƶ�Ч��  
	//�����ָ���󻮣�offset����0��˵��ҳ���ڼ�С����������  
	if (offset < 0)
		m_nCurPage++;
	else if (offset > 0)
		m_nCurPage--;

	//������������ߵ�һҳ�����ұߵ�һҳ  
	if (m_nCurPage < 0)
		m_nCurPage = 0;
	else if (m_nCurPage > 4)
		m_nCurPage = 4;

	Point adjustPoint = Point(-winSize.width * m_nCurPage, 0);
	//���������setContentOffset����һ���������ڶ�������������ʱ��ģ������ö೤��ʱ�����ı�ƫ����  
	this->m_scrollView->setContentOffsetInDuration(adjustPoint, 0.3f);
}