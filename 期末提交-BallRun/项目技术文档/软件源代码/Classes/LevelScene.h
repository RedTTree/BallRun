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

	//������ע�ᴥ���¼���ʵ�ָ��ֵ�touch����  
	virtual bool TouchBegan(Touch * touch, Event * pEvent);
	virtual void TouchMoved(Touch * touch, Event * pEvent);
	virtual void TouchEnded(Touch * touch, Event * pEvent);
	virtual void TouchCancelled(Touch *touch, Event * event);

	//������������У��ÿ���ؿ���λ�ã��Ǹ����ؿ���λ����Ļ������  
	void adjustScrollView(float offset);

private:
	//��CCScrollView��Ϊ�Լ��Ĳ���ӽ���  
	cocos2d::extension::ScrollView * m_scrollView;

	//�������λ��  
	Point m_touchPoint;

	//CCScrollView�ı�����  
	Point m_offsetPoint;

	//��ǰΪ�ڼ����ؿ�  
	int m_nCurPage;
};

#endif /* LevelScene_h */