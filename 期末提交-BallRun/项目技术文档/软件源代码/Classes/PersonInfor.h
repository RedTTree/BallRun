#ifndef TEXT_FILED_TTF_MANAGER
#define TEXT_FILED_TTF_MANAGER
#include "cocos2d.h"

USING_NS_CC;

class keyBoradNotificationLayer :public Layer, public IMEDelegate
{
public:
	keyBoradNotificationLayer();

	//进行点击
	virtual void onClickTrackNode(bool b) = 0;

	//键盘显示的时候执行的通知方法
	virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);

	virtual bool onTouchBegan(Touch *touch, Event *_event);
	virtual void onTouchEnded(Touch *touch, Event *_event);

protected:
	Node* _trackNode;  //被选中的对象节点
	Vec2 _beganPos;    //开始点击区域
};


class TextFiledTTFTest :public keyBoradNotificationLayer{

	virtual void onClickTrackNode(bool b);

	virtual void onEnter();  //被载入场景时候调用

	virtual void menuCloseCallback(Ref* pSender);
};

void runTextFiledTTFManager();

CCScene* cscene();
#endif //EDIT_BOX_MANAGER