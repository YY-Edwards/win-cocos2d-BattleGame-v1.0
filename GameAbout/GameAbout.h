#ifndef example11_1_GameAbout_h
#define example11_1_GameAbout_h
#include "cocos2d.h"


using namespace cocos2d;

class GameAbout:public Layer
{
public:

	//初始化
	virtual bool init();

	/*GameAbout();
	~GameAbout();*/
	virtual void onEnter();

	virtual void onExit();

	void menuEnter(Node * node);

	//创建场景的静态函数
	static cocos2d::Scene* scene();

	// 按钮回调函数
	void menuBacnkCallbck(cocos2d::Ref* pSender);

	// 添加默认的静态创建函数
	CREATE_FUNC(GameAbout);


};


#endif