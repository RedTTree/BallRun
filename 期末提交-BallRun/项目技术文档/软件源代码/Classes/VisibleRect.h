// VisibleRect.h
// �������Ĺ���~~~~

// ���Ӵ�������
// �����ڷ�Ϊ9���֣�������һ�����ס��֡�

#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"

class VisibleRect
{
public:
	// ����ȫ�Ǿ�̬���������÷�ʽ�����磺VisibleRect::center()

	static cocos2d::Rect getVisibleRect();  // ��ÿ��Ӵ��ڴ�С

	static cocos2d::Point left();         // ���ڣ�����
	static cocos2d::Point right();        // ���ڣ�����
	static cocos2d::Point top();          // ���ڣ�����
	static cocos2d::Point bottom();       // ���ڣ�����
	static cocos2d::Point center();       // ���ڣ�����
	static cocos2d::Point leftTop();      // ���ڣ�����
	static cocos2d::Point rightTop();     // ���ڣ�����
	static cocos2d::Point leftBottom();   // ���ڣ�����
	static cocos2d::Point rightBottom();  // ���ڣ�����

private:  // ˽�о�̬
	static void lazyInit();  // ͵���ĳ�ʼ������ȡ����Ƚϳ�������͵��д��һ������������£���ϲ��������^_^����С��:��Ҳϲ��..^_^��
	static cocos2d::Rect s_visibleRect;  //  ��������
};

#endif /* __VISIBLERECT_H__ */