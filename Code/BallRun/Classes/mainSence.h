#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <algorithm>
using namespace std;
USING_NS_CC;
struct _segment{
	Point p1;
	Point p2;
};

class mainSence : public cocos2d::Layer
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
	CREATE_FUNC(mainSence);
private:
	int poi = 1;
	int succe = 1;
	Vec2 speed;
	Point old_point;
	Point pre_point;
	Point preball_point;
	Point curball_point;
	Point cur_point;
	PhysicsWorld* _world;
	_segment seg;
	std::vector<_segment> segment;

};

#endif // __HELLOWORLD_SCENE_H__
