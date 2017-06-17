#ifndef TEXT_FILED_TTF_MANAGER
#define TEXT_FILED_TTF_MANAGER
#include "cocos2d.h"

USING_NS_CC;

class keyBoradNotificationLayer :public Layer, public IMEDelegate
{
public:
	keyBoradNotificationLayer();

	//���е��
	virtual void onClickTrackNode(bool b) = 0;

	//������ʾ��ʱ��ִ�е�֪ͨ����
	virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);

	virtual bool onTouchBegan(Touch *touch, Event *_event);
	virtual void onTouchEnded(Touch *touch, Event *_event);

protected:
	Node* _trackNode;  //��ѡ�еĶ���ڵ�
	Vec2 _beganPos;    //��ʼ�������
};


class TextFiledTTFTest :public keyBoradNotificationLayer{

	virtual void onClickTrackNode(bool b);

	virtual void onEnter();  //�����볡��ʱ�����

	virtual void menuCloseCallback(Ref* pSender);
};

void runTextFiledTTFManager();

CCScene* cscene();
#endif //EDIT_BOX_MANAGER