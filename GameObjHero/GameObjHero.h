#ifndef example11_1_GameobjHero_h
#define example11_1_GameobjHero_h
#include "cocos2d.h"
using namespace cocos2d;


class GameObjHero :public Node//不再使用 TouchDelegate方式来将touch事件捆绑到sprite上。
{								//// Adds touch event listener

	/*
	简单阐述2.x与3.x的事件侦听不同点：
	在2.x中，需要注册一个事件侦听。
	在3.x中，则需要创建一个侦听器的对象，然后定义回调方法，最后将侦听和事件分发器绑定。
	注意，2.x是注册一个事件侦听，在3.x中则是创建一个侦听器对象。这二者有什么不同呢？
	这里分别在2.x中和3.x写一个测试demo，可以看到2.x中一个严重设计bug问题。
	*/



	cocos2d::EventListenerTouchOneByOne* _touchListener;
	//cocos2d::EventListenerKeyboard* _keyboardListener;


public:

	Sprite *lefthand;//左手
	Sprite *righthand;//右手
	Point offset;		//触摸偏移位置
	bool iscontrol;		//是否在控制猪脚

	GameObjHero();
	virtual ~GameObjHero();
	void releasebullet(float dt);//释放子弹
	Rect rect();
	virtual void onEnter()override;
	virtual void onExit()override;

	//触摸相关
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	bool containsTouchLocation(Touch* touch);
	//void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	//void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	
	
	/*virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();*/


};


#endif

