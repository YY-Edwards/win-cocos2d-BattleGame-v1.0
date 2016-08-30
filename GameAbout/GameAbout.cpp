#include"GameAbout\GameAbout.h"
#include"GameMenu\GameMenu.h"

bool GameAbout::init()
{

	if (!Layer::init())
	{
		return false;
	}
	

	//auto size = Director::sharedDirector()->getWinSize();

	auto size = Director::getInstance()->getWinSize();


	//ÿ�л�һ��������Ҫ���³�ʼ�������͸�ͼ�㣿����
	/*�ѵ����ܰѲ���Ҫ��ɾ��������Ҫ�ĸ����£�*/
	//��ʼ������
	auto bg = Sprite::create("Game11_1/backGround.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(size.width / 2, size.height / 2));

	//This��ָ��ǰ���ھ����ָ�룬�������������еĳ�Ա��
	//��this->���г�Ա = ��ֵ���������ܸ����к�����Ա��������Ա��ֵ�ˡ�
	this->addChild(bg, 0, 0);

	//��ʼ������
	auto bgstar = Sprite::create("Game11_1/moon.png");
	bgstar->setAnchorPoint(ccp(0.5, 0));
	bgstar->setScale(0.5);
	bgstar->setPosition(ccp(size.width / 3 , 0));
	this->addChild(bgstar, 1, 1);

	//��ʼ�����ڿ�
	auto kuang = Sprite::create("Game11_1/tb.png");
	kuang->setScale(0.5);
	kuang->setPosition(ccp(size.width / 2 , size.height/2));
	this->addChild(kuang, 2, 2);

	//���ֲ��ֲ���ϵͳ���֣�ʹ���ഴ��ʱ����һ�����飬Ȼ����������������ֲ���
	//kCCTextAlignmentLeft������룩�ķ�ʽ��������á�Marker Felt�����壬Ȼ������λ�ú���ɫ
	char inf[256];
	sprintf(inf, "name:meow war\n\nprogram:Edwards yang\n\nArt design:small fish\n\ncompany:shjh\n\npowered by cocos2D-x");

	auto myjineng = LabelTTF::create(inf, "Marker Felt", 20,
		CCSizeMake(400, 400), kCCTextAlignmentLeft);

	myjineng->setAnchorPoint(ccp(0,1));
	myjineng->setColor(ccc3(200, 200, 200));
	myjineng->setPosition(ccp(50, 400));
	this->addChild(myjineng, 4, 5);//Ϊʲô�еĵط�����Ҫ��this,��Ȼ��Ҫô���Ҫô���쳣

	//��ʼ�����ڱ���
	auto abouttitle = Sprite::create("Game11_1/about.png");
	abouttitle->setScale(0.5);
	abouttitle->setPosition(ccp(size.width / 2, size.height- 400));//��Щλ�ú�������֣����λ�ã�
	this->addChild(abouttitle, 3 , 3);

	//��ʼ�����ذ�ť
	auto back = MenuItemImage::create("Game11_1/backA.png", "Game11_1/backB.png", 
		this, menu_selector(GameAbout::menuBacnkCallbck));
	back->setScale(0.5);
	back->setPosition(ccp(size.width - 20, size.height - 20));//��Щλ�ú�������֣����λ�ã�
	back->setEnabled(false);

	auto mainmenu = Menu::create(back, nullptr);

	mainmenu->setPosition(ccp(0, 0));
	this->addChild(mainmenu, 1, 4);

		return true;



}

Scene* GameAbout::scene()
{
	
	//��������
	auto scene = Scene::create();

	//������ �½�GameAbout����
	auto layer = GameAbout::create();//ͷ�ļ���CREATE_FUNC(GameAbout);����ӵľ�̬�������Զ�����init()

	//��Ӳ�
	scene->addChild(layer);

	return scene;




}

void GameAbout::onEnter()
{
	Layer::onEnter();
	//�������ʱ�����в˵�����붯��
	//auto size = Director::sharedDirector()->getWinSize();
	auto size = Director::getInstance()->getWinSize();
	auto mainmenu = this->getChildByTag(4);
	mainmenu->setPositionX(-100);
	mainmenu->
		runAction(Sequence::create(EaseElasticIn::create(MoveBy::create
		(0.1, ccp(100, 0))),
		CallFuncN::create(this, callfuncN_selector(GameAbout::menuEnter)), NULL));

	//���ٶȶ���
	auto title = this->getChildByTag(3);
	title->setPositionY(size.height + 20);
	title->runAction(EaseElasticIn::create(MoveBy::create
		(0.1, ccp(0, -400))));

	auto bgstar = this->getChildByTag(1);
	bgstar->setPositionX(size.width/3 );
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

void GameAbout::menuEnter(Node*)
{
	//�˵�����󣬲˵�������ЧŶ
	
	auto  mainmenu = this->getChildByTag(4);

	//3.0�汾��û��Array��ȡ����֮��������
	//auto temp = mainmenu->getChildren();

	
	for(auto e : mainmenu->getChildren())//���ַ�ʽ��ʽҲ�ǶԵġ�
	{
		((MenuItemImage*)e)->setEnabled(true);

	}


	//((MenuItemImage*)temp->objectAtIndex(0))->setEnabled(true);



}

void GameAbout::menuBacnkCallbck(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(GameMenu::scene());
	//����һ��
	//ctor::sharedDirector()->replaceScene(GameMenu::scene());


}