#ifndef example11_1_GameMenu_h
#define example11_1_GameMenu_h
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;


class GameMenu:public Layer
{
public:
	
	bool issound;
	MenuItemImage *soundItem;

	void menuEnter(Node * node);

	// ��ť�ص�����
	void menuSoundCallbck(cocos2d::Ref* pSender);
	void menuNewGameCallbck(cocos2d::Ref* pSender);
	void menuContinueCallbck(cocos2d::Ref* pSender);
	void menuAboutCallbck(cocos2d::Ref* pSender);

	virtual void onEnter();
	virtual void onExit();

	//���������ľ�̬����
	static cocos2d::Scene* scene();

	//��ʼ��
	virtual bool init();


	// ���Ĭ�ϵľ�̬��������
	CREATE_FUNC(GameMenu);



};





#endif