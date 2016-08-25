#include"GameAbout\GameAbout.h"
#include"GameMenu\GameMenu.h"

bool GameAbout::init()
{

	if (!Layer::init())
	{
		return false;
	}
	

	auto size = Director::sharedDirector()->getWinSize();

	//每切换一个场景都要重新初始化背景和各图层？？？
	/*难道不能把不需要的删除掉，需要的给留下？*/
	//初始化背景
	auto bg = Sprite::create("Game11_1/backGround.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(size.width / 2, size.height / 2));

	//This是指向当前窗口句柄的指针，如果你想调用类中的成员，
	//用this->类中成员 = 赋值；这样就能给类中函数成员里面的类成员赋值了。
	this->addChild(bg, 0, 0);

	//初始化星球
	auto bgstar = Sprite::create("Game11_1/moon.png");
	bgstar->setAnchorPoint(ccp(0.5, 0));
	bgstar->setScale(0.5);
	bgstar->setPosition(ccp(size.width / 3 * 1, 0));
	bgstar->addChild(bgstar, 1, 1);

	//初始化关于框
	auto kuang = Sprite::create("Game11_1/tb.png");
	kuang->setScale(0.5);
	kuang->setPosition(ccp(size.width / 2 , size.height/2));
	kuang->addChild(kuang, 2, 2);

	//文字部分采用系统文字，使用类创建时定义一个语句块，然后在这个区域内文字采用
	//kCCTextAlignmentLeft（左对齐）的方式，另外采用“Marker Felt”字体，然后设置位置和颜色
	char inf[256];
	sprintf(inf, "name:meow war\n\n program:Edwards man\n\nart design:PX\n\ncompany: shjh\n\n  powered by cocos2D - x");

	auto myjineng = LabelTTF::create(inf, "Marker Felt", 40,
		CCSizeMake(400, 400), kCCTextAlignmentLeft);

	myjineng->setAnchorPoint(ccp(0.1));
	myjineng->setColor(ccc3(200, 200, 200));
	myjineng->setPosition(ccp(50, 600));
	myjineng->addChild(myjineng);

	//初始化关于标题
	auto abouttitle = Sprite::create("Game11_1/about.png");
	abouttitle->setScale(0.5);
	abouttitle->setPosition(ccp(size.width / 2, size.height- 20));//这些位置合适吗？奇怪？相对位置？
	this->addChild(abouttitle, 3 , 3);

	//初始化返回按钮
	auto back = MenuItemImage::create("Game11_1/backA.png", "Game11_1/backB.png", 
		this, menu_selector(GameAbout::menuBacnkCallbck));
	back->setScale(0.5);
	back->setPosition(ccp(size.width - 20, size.height - 20));//这些位置合适吗？奇怪？相对位置？
	back->setEnabled(false);

	auto mainmenu = Menu::create(back, NULL);

	mainmenu->setPosition(ccp(0, 0));
	this->addChild(mainmenu, 3, 4);

		return true;



}

Scene* GameAbout::scene()
{
	
	//创建场景
	auto scene = Scene::create();

	//创建层 新建GameAbout对象
	auto layer = GameAbout::create();//头文件中CREATE_FUNC(GameAbout);宏添加的静态函数，自动调用init()

	//添加层
	scene->addChild(layer);

	return scene;




}

void GameAbout::onEnter()
{
	Layer:onEnter();
	//界面进入时，运行菜单项进入动作
	auto size = Director::sharedDirector()->getWinSize();
	auto mainmenu = this->getChildByTag(4);
	mainmenu->setPositionX(-100);
	mainmenu->
		runAction(Sequence::create(EaseElasticIn::create(MoveBy::create
		(0.5, ccp(100, 0))),
		CallFuncN::create(this, callfuncN_selector(GameAbout::menuEnter)), NULL));

	//加速度动作
	auto title = this->getChildByTag(3);
	title->setPositionY(size.height + 20);
	title->runAction(EaseElasticIn::create(MoveBy::create
		(0.5, ccp(0, -400))));

	auto bgstar = this->getChildByTag(1);
	bgstar->setPositionX(size.width/3*2);
	bgstar->runAction(MoveBy::create
		(0.5, ccp(-size.width/3, 0)));

	auto kuang = this->getChildByTag(2);
	kuang->setPositionX(-200);
	kuang->runAction(EaseElasticIn::create(MoveTo::create
		(0.5, ccp(size.width/2, size.height/2))));


}

void GameAbout::onExit()
{
	Layer::onExit();

}

void GameAbout::menuEnter(Node* node)
{
	//菜单进入后，菜单项点击有效哦
	
	auto  mainmenu = this->getChildByTag(4);


	Vector<CCMenuItemImage*>temp = mainmenu->getChildren();

	Vector<CCMenuItemImage*>temp;



	(((mainmenu->getChildren())->objectAtIndex(0)->setEnabled(true);



}

void GameAbout::menuBacnkCallbck(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(GameMenu::scene());
	//功能一样
	//ctor::sharedDirector()->replaceScene(GameMenu::scene());


}