#ifndef example11_1_GameobjHero_h
#define example11_1_GameobjHero_h
#include "cocos2d.h"
using namespace cocos2d;


class GameObjHero :public Node//����ʹ�� TouchDelegate��ʽ����touch�¼�����sprite�ϡ�
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

	Sprite *lefthand;//����
	Sprite *righthand;//����
	Point offset;		//����ƫ��λ��
	bool iscontrol;		//�Ƿ��ڿ������

	GameObjHero();
	virtual ~GameObjHero();
	void releasebullet(float dt);//�ͷ��ӵ�
	Rect rect();
	virtual void onEnter()override;
	virtual void onExit()override;

	//�������
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

