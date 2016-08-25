#ifndef example11_1_GameobjEnemy_h
#define example11_1_GameobjEnemy_h
#include "cocos2d.h"
using namespace cocos2d;


class GameObjEnemy :public Node
{
public:

	CCSprite *boom;//爆炸
	CCSprite *mainbody;//狗博士主体
	bool islife;		//敌人是否活着
	short type;


	GameObjEnemy();
	virtual ~GameObjEnemy();
	void setdie();//狗博士死亡函数
	void restart(Node* dd);//狗博士复位
	void movestart();//设置狗博士的移动方式
	void releasebullet(float dt);//释放子弹
	void setType(short var);

	virtual void onEnter();
	virtual void onExit();


};


#endif

