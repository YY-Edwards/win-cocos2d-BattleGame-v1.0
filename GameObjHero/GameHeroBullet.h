#ifndef example11_1_GameHeroBullet_h
#define example11_1_GameHeroBullet_h
#include "cocos2d.h"
using namespace cocos2d;



class GameHeroBullet :public CCNode
{

public:
	bool isvisable;//�ӵ��Ƿ���ʹ��
	GameHeroBullet();
	virtual ~GameHeroBullet();
	void setIsVisable();//�����ӵ���ʹ��
	void setIsNotVisable(Node* dd);//�����ӵ�û��ʹ��
	bool getIsvisable();//����ӵ��Ƿ���ʹ��

	virtual void onEnter();
	virtual void onExit();

};


#endif