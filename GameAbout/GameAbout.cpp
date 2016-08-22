#include"GameAbout\GameAbout.h"

bool GameAbout::init()
{

	if (!Layer::init())
	{
		return false;
	}
	

	auto size = Director::sharedDirector()->getWinSize();
	//初始化背景
	auto bg = Sprite::create("Game11_1/backGround.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(size.width / 2, size.height / 2));

	//This是指向当前窗口句柄的指针，如果你想调用类中的成员，
	//用this->类中成员 = 赋值；这样就能给类中函数成员里面的类成员赋值了。
	this->addChild(bg, 0, 0);

	//初始化星球
	auto bgstar = Sprite::create("Game11_1/moon.png");














}