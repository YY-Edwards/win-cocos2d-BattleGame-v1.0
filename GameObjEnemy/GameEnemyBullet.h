#ifndef example11_1_GameEnemyBullet_h
#define example11_1_GameEnemyBullet_h
#include "cocos2d.h"
using namespace cocos2d;



class GameEnemyBullet :public CCNode
{

public:

	bool isvisable;//�ӵ��Ƿ���ʹ��
	GameEnemyBullet();
	virtual ~GameEnemyBullet();
	void setIsVisable();//�����ӵ���ʹ��
	void setIsNotVisable(Node * node);//�����ӵ�û��ʹ��
	bool getIsvisable();//����ӵ��Ƿ���ʹ��

	virtual void onEnter();
	virtual void onExit();

};


#endif