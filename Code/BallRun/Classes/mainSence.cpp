#include "mainSence.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;



Scene* mainSence::createScene()
{
   
    auto scene = Scene::create();
    auto layer = mainSence::create();
    scene->addChild(layer);
    return scene;
}

bool mainSence::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("main.csb");

    addChild(rootNode);
	
	Button* game = (Button*)rootNode->getChildByName("Button_1");
	game->addTouchEventListener(this, toucheventselector(mainSence::onSwitch));

    return true;
}

void mainSence::onSwitch(Ref*, TouchEventType type){
	printf("onchange");
}
