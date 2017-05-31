#ifndef __SampleGame1__GameOverScene__
#define __SampleGame1__GameOverScene__

#include "cocos2d.h"
#include <algorithm>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace std;

class GameOverLayer : public cocos2d::LayerColor
{
public:
    GameOverLayer():_label(NULL) {};
    virtual ~GameOverLayer();
    bool init();
	void btnRetryed(Ref *pSender, Widget::TouchEventType type);
	void btnNexted(Ref *pSender, Widget::TouchEventType type);
    CREATE_FUNC(GameOverLayer);
    
    void gameOverDone();
    
    CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);
};

class GameOverScene : public cocos2d::Scene
{
public:
    GameOverScene():_layer(NULL) {};
    ~GameOverScene();
    bool init();
    CREATE_FUNC(GameOverScene);
    
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};

#endif /* defined(__SampleGame1__GameOverScene__) */
