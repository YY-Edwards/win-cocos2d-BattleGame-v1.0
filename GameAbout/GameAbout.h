#ifndef example11_1_GameAbout_h
#define example11_1_GameAbout_h
#include "cocos2d.h"


using namespace cocos2d;

class GameAbout:public Layer
{
public:

	//��ʼ��
	virtual bool init();

	/*GameAbout();
	~GameAbout();*/
	virtual void onEnter();

	virtual void onExit();

	void menuEnter(Node * node);

	//���������ľ�̬����
	static cocos2d::Scene* scene();

	// ��ť�ص�����
	void menuBacnkCallbck(cocos2d::Ref* pSender);

	// ���Ĭ�ϵľ�̬��������
	CREATE_FUNC(GameAbout);


};


#endif