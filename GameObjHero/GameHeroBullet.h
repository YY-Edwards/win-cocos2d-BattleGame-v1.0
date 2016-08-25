#ifndef example11_1_GameHeroBullet_h
#define example11_1_GameHeroBullet_h
#include "cocos2d.h"
using namespace cocos2d;



class GameHeroBullet :public CCNode
{

public:
	bool isvisable;//子弹是否在使用
	GameHeroBullet();
	virtual ~GameHeroBullet();
	void setIsVisable();//设置子弹在使用
	void setIsNotVisable(Node* dd);//设置子弹没有使用
	bool getIsvisable();//获得子弹是否在使用

	virtual void onEnter();
	virtual void onExit();

};


#endif