#include"GameMark.h"

void GameMark::onEnter()
{
	CCNode::onEnter();
	auto size = CCDirector::sharedDirector()->getWinSize();

	this->setContentSize(size);

	bits = Array::createWithCapacity(5);

	 // 分数标题

	 auto title = Sprite::create("Game11_1/score.png");
	 title->setPosition(ccp(size.width / 2 + 40, size.height - 15));
	 title->setScale(0.5);
	 addChild(title);

	 //数字按位设置
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

	 bits->retain();//保留成员变量，不能被自动释放
	 mark = 0;

}


void GameMark::addnumber(int var)
{
	//分数，按位设置数字

	mark += var;
	int temp = mark % 10;

	//设置个位
	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(0))->setTextureRect(CCRectMake((temp-1)*26, 0, 26, 31));//根据数字然后按位去取（根据宽度来计算）

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(0))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//设置十位
	temp = (mark % 100)/10;

	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(1))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//根据数字然后按位去取（根据宽度来计算）

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(1))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//设置百位
	temp = (mark % 1000) / 100;
	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(2))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//根据数字然后按位去取（根据宽度来计算）

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(2))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//设置千位
	temp = (mark % 10000) / 1000;
	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(3))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//根据数字然后按位去取（根据宽度来计算）

	}
	else{

		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(3))->setTextureRect(CCRectMake(234, 0, 26, 31));

	}

	//设置万位
	temp = mark / 10000;

	if (temp > 0)
	{
		((Sprite*)bits->objectAtIndex(0))->setTexture(ui);
		((Sprite*)bits->objectAtIndex(4))->setTextureRect(CCRectMake((temp - 1) * 26, 0, 26, 31));//根据数字然后按位去取（根据宽度来计算）

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
