#include"GameAbout\GameAbout.h"

bool GameAbout::init()
{

	if (!Layer::init())
	{
		return false;
	}
	

	auto size = Director::sharedDirector()->getWinSize();
	//��ʼ������
	auto bg = Sprite::create("Game11_1/backGround.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(size.width / 2, size.height / 2));

	//This��ָ��ǰ���ھ����ָ�룬�������������еĳ�Ա��
	//��this->���г�Ա = ��ֵ���������ܸ����к�����Ա��������Ա��ֵ�ˡ�
	this->addChild(bg, 0, 0);

	//��ʼ������
	auto bgstar = Sprite::create("Game11_1/moon.png");














}