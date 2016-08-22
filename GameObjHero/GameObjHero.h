#ifndef example11_1_GameobjHero_h
#define example11_1_GameobjHero_h
#include "cocos2d.h"
using namespace cocos2d;


class GameObjHero :public CCNode//����ʹ�� TouchDelegate��ʽ����touch�¼�����sprite�ϡ�
{								//// Adds touch event listener

	/*
	�򵥲���2.x��3.x���¼�������ͬ�㣺
	��2.x�У���Ҫע��һ���¼�������
	��3.x�У�����Ҫ����һ���������Ķ���Ȼ����ص�����������������¼��ַ����󶨡�
	ע�⣬2.x��ע��һ���¼���������3.x�����Ǵ���һ�������������������ʲô��ͬ�أ�
	����ֱ���2.x�к�3.xдһ������demo�����Կ���2.x��һ���������bug���⡣
	*/



	cocos2d::EventListenerTouchOneByOne* _touchListener;
	//cocos2d::EventListenerKeyboard* _keyboardListener;


public:

	CCSprite *lefthand;//����
	CCSprite *righthand;//����
	CCPoint offset;		//����ƫ��λ��
	bool iscontrol;		//�Ƿ��ڿ������

	GameObjHero();
	virtual ~GameObjHero();
	void releasebullet(float dt);//�ͷ��ӵ�
	CCRect rect();
	virtual void onEnter();
	virtual void onExit();

	//�������
	bool containsTouchLocation(CCTouch* touch);
	virtual bool onTouchBegan(CCTouch* touch, CCEvent* event);
	virtual bool onTouchMoved(CCTouch* touch, CCEvent* event);
	virtual bool onTouchEnded(CCTouch* touch, CCEvent* event);

	//void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	//void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	
	
	/*virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();*/


};


#endif

