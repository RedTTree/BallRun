#include "cocos2d.h"
#include "cocos-ext.h"  
USING_NS_CC_EXT;
using namespace cocos2d;

class EditText : public cocos2d::Layer, public EditBoxDelegate{
public:
	std::string m_name;
	std::string m_password;

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

	virtual bool init();
	static cocos2d::CCScene* scene();

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(EditText);
};