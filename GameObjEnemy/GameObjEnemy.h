#ifndef example11_1_GameobjEnemy_h
#define example11_1_GameobjEnemy_h
#include "cocos2d.h"
using namespace cocos2d;


class GameObjEnemy :public Node
{
public:

	CCSprite *boom;//��ը
	CCSprite *mainbody;//����ʿ����
	bool islife;		//�����Ƿ����
	short type;


	GameObjEnemy();
	virtual ~GameObjEnemy();
	void setdie();//����ʿ��������
	void restart(Node* dd);//����ʿ��λ
	void movestart();//���ù���ʿ���ƶ���ʽ
	void releasebullet(float dt);//�ͷ��ӵ�
	void setType(short var);

	virtual void onEnter();
	virtual void onExit();


};


#endif

