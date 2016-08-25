#include"GameMenu\GameMenu.h"
#include"GameMain\GameMain.h"
#include"GameAbout\GameAbout.h"

bool GameMenu::init()
{ 
	if (!Layer::init())
	{
		false;
	}

	//主菜单的实现：
	//只需要把界面控件加入布景层，然后设置按钮的回调函数就可以了
	auto size = Director::sharedDirector()->getWinSize();

	//初始化背景
	auto bg = Sprite::create("Game11_1/backGround.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(size.width / 2, size.height / 2));//正中央
	this->addChild(bg, 0, 0);

	//初始化背景星球
	auto bgstar = Sprite::create("Game11_1/moon.png");
	//锚点是指节点在进行形状变换、位置变动时依据的基准点。
	bgstar->setAnchorPoint(ccp(0.5, 0));
	bgstar->setScale(0.5);
	bgstar->setPosition(ccp(size.width / 3*2, 0));
	this->addChild(bgstar, 1, 1);

	//初始化标题
	auto title = Node::create();
	title->setContentSize(CCSizeMake(size.width - 40, 50));

	auto ptmLabel = Sprite::create("Game11_1/meowstar.png");
	ptmLabel->setScale(0.5);
	ptmLabel->setPosition(ccp(0, 30));//这些位置合适吗？奇怪？相对位置？
	title->addChild(ptmLabel);

	auto ptbLabel =Sprite::create("Game11_1/battle.png");
	ptbLabel->setScale(0.5);
	ptbLabel->setPosition(ccp(0, -30));//相对位置？相对于title吗？各相距30单位长？
	title->addChild(ptbLabel);

	title->setPosition(ccp(size.width / 2, size.height - 80));
	this->addChild(title, 2, 2);

	//初始化按钮
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

	//使用按钮创建菜单
	auto mainmenu = Menu::create(newGameItem, continueItem, aboutItem,
		soundItem, NULL);
	mainmenu->setPosition(ccp(0, 0));
	this->addChild(mainmenu, 1, 3);

	//初始化声音部分
	issound = true;//是否开启声音参数

	//貌似这样就可以了
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


//为按钮加入动作可以使游戏更生动
void GameMenu::onEnter()
{
	Layer::onEnter();

	auto size = Director::sharedDirector()->getWinSize();

	//界面进入时，运行菜单项进入动作
	auto mainmenu = this->getChildByTag(3);
	mainmenu->setPositionX(-200);
	mainmenu->
		runAction(Sequence::create(EaseElasticIn::create(MoveTo::create
		(0.5, ccp(0, 0))), CallFuncN::create(this, callfuncN_selector(GameMenu::menuEnter)), NULL));

	
	//标题进入动作
	auto title = this->getChildByTag(2);
	title->setPositionY(size.height + 20);

	//按弹性曲线缓动进入的动作
	//用内部动作创建EaseElasticIn动作，缓动曲线周期（弧度值）是0.3。
	title->runAction(EaseElasticIn::create(MoveBy::create(0.5, ccp(0, -100))));

	auto bgstar = this->getChildByTag(1);
	bgstar->setPositionY(size.height /3);
	bgstar->runAction(MoveBy::create(0.5, ccp(size.width/3, 0)));

}

void GameMenu::menuEnter(Node * node)
{
	//菜单进入后，菜单项点击有效
	Node* mainmenu = this->getChildByTag(3);

	Vector<Node*>temp = mainmenu->getChildren();

	for (auto& e: temp)
	{
		;
	}

	//Array* temp = mainmenu->getChildren();

	//for (size_t i = 0; i < temp->count(); i++)
	//{
	//	((MenuItemImage*)temp->objectAtIndex(i))->setEnabled(true);
	//}



}

void GameMenu::onExit()
{
	Layer::onExit();


}

void GameMenu::menuNewGameCallbck(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(GameMain::scene());

}

void GameMenu::menuSoundCallbck(cocos2d::Ref* pSender)
{
	if (!issound)
	{
		soundItem->setNormalImage(Sprite::create("Game11_1/sound-on-A.png"));
		soundItem->setDisabledImage(Sprite::create("Game11_1/sound-on-B.png"));
		
		//play music
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Game11_1/Fade.wav", true);

		issound = true;

	}
	else
	{
		soundItem->setNormalImage(Sprite::create("Game11_1/sound-off-A.png"));
		soundItem->setDisabledImage(Sprite::create("Game11_1/sound-off-B.png"));

		//stop music
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();

		issound = false;


	}
	
	
	
	Director::getInstance()->replaceScene(GameMain::scene());

}

void GameMenu::menuContinueCallbck(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(GameMain::scene());

}

void GameMenu::menuAboutCallbck(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(GameAbout::scene());

}

Scene* GameMenu::scene()
{

	//创建场景
	auto scene = Scene::create();

	//创建层 新建GameAbout对象
	auto layer = GameMenu::create();//头文件中CREATE_FUNC(GameAbout);宏添加的静态函数，自动调用init()

	//添加层
	scene->addChild(layer);

	return scene;


}

