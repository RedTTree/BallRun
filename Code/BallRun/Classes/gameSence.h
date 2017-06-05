#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <algorithm>
#include "GameTimer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace std;
USING_NS_CC;

class gameSence : public cocos2d::Layer
{
public:

	Sprite* ball;
	Sprite* paddle;
	Sprite* edgeSp;
	Node* m_streak;

	PhysicsWorld* m_world;

	void setPhyWorld(PhysicsWorld* world){ m_world = world; };

	void tick(float dt);

	virtual void onEnter();
	void btnRetryed(Ref *pSender, Widget::TouchEventType type);
	void btnBacked(Ref *pSender, Widget::TouchEventType type);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	void update(float dt);

	bool onContactBegin(cocos2d::PhysicsContact& contact);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(gameSence);
private:
	int poi = 1;
	int succe = 1;
	GameTimer * m_timer;
	Vec2 speed;
	Point old_point;
	Point pre_point;
	Point preball_point;
	Point curball_point;
	Point cur_point;
	PhysicsWorld* _world;

};

#endif // __HELLOWORLD_SCENE_H__
