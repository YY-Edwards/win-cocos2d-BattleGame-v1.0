#ifndef example11_1_GameMain_h
#define example11_1_GameMain_h
#include "cocos2d.h"
#include"../GameObjHero/GameObjHero.h"
#include"../GameObjEnemy/GameObjEnemy.h"
#include"../GameMark/GameMark.h"
#include"../GameObjHero/GameHeroBullet.h"
#include"../GameObjEnemy/GameEnemyBullet.h"
#include"GameMenu\GameMenu.h"

using namespace cocos2d;


class GameMain:public Layer
{
public:

	Sprite *bg1, *bg2;
	GameObjHero *hero;

	
	Vector<Node*>enemys;//������ʱ�����趨��С��
	Vector<Node*>bullets;
	Vector<Node*>enemybullets;

	//Array *enemys;
	//Array *bullets;
	//Array *enemybullets;


	GameObjEnemy *enemy;
	GameMark *gamemark;
	Sprite *gameover;

	MenuItemImage *pCloseItem;

	int blood;
	Sprite *blood1, *blood2, *blood3;

	bool isreduce;
	bool isover;


	
	void setover();
	virtual void update(float time);
	bool isCollion(Point p1, Point p2, int w1, int h1, int w2, int h2);
	void setherohurt();
	//void setenemyhurt();
	void resetreduce(float da);

	void releaseenemyBullet(int x, int y);
	void releaseheroBullet(int x, int y);

	//GameMain();
	//~GameMain();

	//���������ľ�̬����
	static cocos2d::Scene* scene();

	//��ʼ��
	virtual bool init();

	// �˵��ص�����
	void menuBackCallback(cocos2d::Ref* pSender);

	// ���Ĭ�ϵľ�̬��������
	CREATE_FUNC(GameMain);

};





#endif