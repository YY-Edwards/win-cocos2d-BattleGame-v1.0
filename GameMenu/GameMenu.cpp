#include"GameMenu\GameMenu.h"

bool GameMenu::init()
{ 
	if (!Layer::init())
	{
		false;
	}

	//���˵���ʵ�֣�
	//ֻ��Ҫ�ѽ���ؼ����벼���㣬Ȼ�����ð�ť�Ļص������Ϳ�����
	auto size = Director::sharedDirector()->getWinSize();

	//��ʼ������
	auto bg = Sprite::create("Game11_1/backGround.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(size.width / 2, size.height / 2));//������
	this->addChild(bg, 0, 0);

	//��ʼ����������
	auto bgstar = Sprite::create("Game11_1/moon.png");
	//ê����ָ�ڵ��ڽ�����״�任��λ�ñ䶯ʱ���ݵĻ�׼�㡣
	bgstar->setAnchorPoint(ccp(0.5, 0));
	bgstar->setScale(0.5);
	bgstar->setPosition(ccp(size.width / 3*2, 0));
	this->addChild(bgstar, 1, 1);

	//��ʼ������
	auto title = Node::create();
	title->setContentSize(CCSizeMake(size.width - 40, 50));

	auto ptmLabel = Sprite::create("Game11_1/meowstar.png");
	ptmLabel->setScale(0.5);
	ptmLabel->setPosition(ccp(0, 30));//��Щλ�ú�������֣����λ�ã�
	title->addChild(ptmLabel);

	auto ptbLabel =Sprite::create("Game11_1/battle.png");
	ptbLabel->setScale(0.5);
	ptbLabel->setPosition(ccp(0, -30));//���λ�ã������title�𣿸����30��λ����
	title->addChild(ptbLabel);

	title->setPosition(ccp(size.width / 2, size.height - 80));
	this->addChild(title, 2, 2);

	//��ʼ����ť
	auto newGameItem = MenuItemImage::create("Game11_1/newgameA.png",
		"Game11_1/newgameB.png", this , menu_selector(GameMenu::menuNewGameCallbck));
	newGameItem->setScale(0.5);
	newGameItem->setPosition(ccp(size.width / 2, size.height / 2 - 20));
	newGameItem->setEnabled(false);

	auto continueItem = MenuItemImage::create("Game11_1/continueA.png",
		"Game11_1/continueB.png", this, menu_selector(GameMenu::menuContinueCallbck));
	continueItem->setScale(0.5);
	continueItem->setPosition(ccp(size.width / 2, size.height / 2 - 80));
	continueItem->setEnabled(false);

	auto aboutItem = MenuItemImage::create("Game11_1/aboutA.png",
		"Game11_1/abouteB.png", this, menu_selector(GameMenu::menuAboutCallbck));
	aboutItem->setScale(0.5);
	aboutItem->setPosition(ccp(size.width / 2, size.height / 2 - 140));
	aboutItem->setEnabled(false);

	soundItem = MenuItemImage::create("Game11_1/sound-on-A.png",
		"Game11_1/sound-on-B.png", this, menu_selector(GameMenu::menuSoundCallbck));
	aboutItem->setScale(0.5);
	aboutItem->setPosition(ccp(40, 40));
	aboutItem->setEnabled(false);

	//ʹ�ð�ť�����˵�
	auto mainmenu = Menu::create(newGameItem, continueItem, aboutItem,
		soundItem, NULL);
	mainmenu->setPosition(ccp(0, 0));
	this->addChild(mainmenu, 1, 3);

	//��ʼ����������
	issound = true;//�Ƿ�����������

	//ò�������Ϳ�����
	/*SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
		std::string(FileUtils::sharedFileUtils()->fullPathForFilename("Game11_1/Fade.wav")).c_str);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.9);	
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		std::string(FileUtils::sharedFileUtils()->fullPathForFilename("Game11_1/Fade.wav")).c_str, true);*/

	// preload background music and effect
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Game11_1/Fade.wav");
	// set default volume:getInstance()->preloadEffect( EFFECT_FILE );
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.9);

	//play music
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Game11_1/Fade.wav", true);

	return true;

}


//Ϊ��ť���붯������ʹ��Ϸ������
void GameMenu::onEnter()
{
	Layer::onEnter();

	auto size = Director::sharedDirector()->getWinSize();

	//�������ʱ�����в˵�����붯��
	auto mainmenu = this->getChildByTag(3);
	mainmenu->setPositionX(-200);
	mainmenu->
		runAction(Sequence::create(EaseElasticIn::create(MoveTo::create
		(0.5, ccp(0, 0))), CallFuncN::create(this, callfuncN_selector(GameMenu::menuEnter)), NULL));

	
	//������붯��
	auto title = this->getChildByTag(2);
	title->setPositionY(size.height + 20);

	//���������߻�������Ķ���
	//���ڲ���������EaseElasticIn�����������������ڣ�����ֵ����0.3��
	title->runAction(EaseElasticIn::create(MoveBy::create(0.5, ccp(0, -100))));

	auto bgstar = this->getChildByTag(1);
	bgstar->setPositionY(size.height /3);
	bgstar->runAction(MoveBy::create(0.5, ccp(size.width/3, 0)));

}