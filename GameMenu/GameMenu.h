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

	// 按钮回调函数
	void menuSoundCallbck(cocos2d::Ref* pSender);
	void menuNewGameCallbck(cocos2d::Ref* pSender);
	void menuContinueCallbck(cocos2d::Ref* pSender);
	void menuAboutCallbck(cocos2d::Ref* pSender);

	virtual void onEnter();
	virtual void onExit();

	//创建场景的静态函数
	static cocos2d::Scene* scene();

	//初始化
	virtual bool init();


	// 添加默认的静态创建函数
	CREATE_FUNC(GameMenu);



};





#endif