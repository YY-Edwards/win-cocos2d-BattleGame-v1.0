#include"GameMark.h"

void GameMark::onEnter()
{
	CCNode::onEnter();
	auto size = CCDirector::sharedDirector()->getWinSize();

	this->setContentSize(size);

	bits = Array::createWithCapacity(5);

	 // ��������

	 auto title = Sprite::create("Game11_1/score.png");
	 title->setPosition(ccp(size.width / 2 + 40, size.height - 15));
	 title->setScale(0.5);
	 addChild(title);

	 //���ְ�λ����
	 //for (auto &item : touches)

	 for (int i = 0; i < 5; i++)
	 {
		 auto shu = Sprite::create("Game11_1/shu.png");

		 ui = shu->getTexture();

		 shu->setScale(0.5);
		 shu->setTextureRect(CCRectMake(234, 0, 26, 31));
		 shu->setPosition(ccp(size.width - 15 - i * 15, size.height - 15));
		 bits->addObject(shu);
		 addChild(shu);

	 }

	 bits->retain();//������Ա���������ܱ��Զ��ͷ�
	 mark = 0;

}


void GameMark::addnumber(int var)
{
	//��������λ��������

	mark += var;
	int temp = mark % 10;

	//���ø�λ
	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(0))->setTextureRect(CCRectMake((temp-1)*26, 0, 26, 31));//��������Ȼ��λȥȡ�����ݿ�������㣩

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(0))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//����ʮλ
	temp = (mark % 100)/10;

	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(1))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//��������Ȼ��λȥȡ�����ݿ�������㣩

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(1))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//���ð�λ
	temp = (mark % 1000) / 100;
	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(2))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//��������Ȼ��λȥȡ�����ݿ�������㣩

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(2))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//����ǧλ
	temp = (mark % 10000) / 1000;
	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(3))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//��������Ȼ��λȥȡ�����ݿ�������㣩

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(3))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//������λ
	temp = mark / 10000;

	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(4))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//��������Ȼ��λȥȡ�����ݿ�������㣩

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(4))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

}

GameMark::GameMark()
{
	;
}
GameMark::~GameMark()
{
	;
}

void GameMark::onExit()
{
	
	Node::onExit();


}
