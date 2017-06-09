// VisibleRect.h
// 星月倾心贡献~~~~

// 可视窗口区域
// 将窗口分为9部分，类似与一个“米”字。

#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"

class VisibleRect
{
public:
	// 以下全是静态方法，调用方式：例如：VisibleRect::center()

	static cocos2d::Rect getVisibleRect();  // 获得可视窗口大小

	static cocos2d::Point left();         // 窗口：左中
	static cocos2d::Point right();        // 窗口：右中
	static cocos2d::Point top();          // 窗口：上中
	static cocos2d::Point bottom();       // 窗口：下中
	static cocos2d::Point center();       // 窗口：中中
	static cocos2d::Point leftTop();      // 窗口：左上
	static cocos2d::Point rightTop();     // 窗口：右上
	static cocos2d::Point leftBottom();   // 窗口：左下
	static cocos2d::Point rightBottom();  // 窗口：右下

private:  // 私有静态
	static void lazyInit();  // 偷懒的初始化（获取代码比较长，所以偷懒写在一个函数里）（星月：我喜欢。。。^_^）（小白:我也喜欢..^_^）
	static cocos2d::Rect s_visibleRect;  //  可视区域
};

#endif /* __VISIBLERECT_H__ */