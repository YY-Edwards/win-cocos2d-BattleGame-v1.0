#include "GameMain.h"



bool GameMain::init()
{
	//先调用父类
	if (!Layer::init())
	{

		return false;
	}

	//导演第一次出现，获取屏幕大小
	Size size = Director::sharedDirector()->getWinSize();

	//创建背景
	bg1 = Sprite::create("Game11_1/backGround.png");
	bg1->setScale(0.5);
	bg2 = Sprite::create("Game11_1/backGround.png");
	bg2->setScale(0.5);

	bg1->setAnchorPoint(ccp(0, 0));
	bg2->setAnchorPoint(ccp(0, 0));
	
	bg1->setPosition(ccp(0, 0));
	bg2->setPosition(ccp(0, size.height));

	this->addChild(bg1, 0);
	this->addChild(bg2, 0);

	//创建猪脚

	hero = new GameObjHero();
	hero->setPosition(ccp(size.width / 2, -50));
	hero->setScale(0.5);
	addChild(hero, 2, 1);
	hero->runAction(MoveBy::create(0.5, ccp(0, 150)));

	//创建敌人
	enemys = Array::createWithCapacity(3);

	for (int i = 0; i < 3; i++)
	{
		int type = 1 + i;
		auto enemy = new GameObjEnemy();
		enemy->setPosition(ccp(size.width / 4 * type, size.height + 50));

		enemy->setScale(0.5);
		enemy->setType(type);
		enemys->addObject(enemy);
		addChild(enemy, 1);
		enemy->movestart();

	}

	enemys->retain();

	//创建血量UI
	blood = 3;
	//批处理绘制
	auto ui = SpriteBatchNode::create("Game11_1/cat.png");

	blood1 = Sprite::createWithTexture(ui->getTexture());
	blood1->setPosition(ccp(20, size.height - 20));
	blood1->setScale(0.2);
	ui->addChild(blood1);////child加入节点树中，其默认ZOrder值为0.如果这个孩子加入的
						//是一个正在运行的节点，onEnter函数和onEnterTransitionDidFinish函数将会被调用。

	blood2 = Sprite::createWithTexture(ui->getTexture());
	blood2->setPosition(ccp(50, size.height - 20));
	blood2->setScale(0.2);
	ui->addChild(blood2);

	blood3 = Sprite::createWithTexture(ui->getTexture());//创建贴图精灵
	blood3->setPosition(ccp(80, size.height - 20));//放置位置
	blood3->setScale(0.2);//根据资源缩放合适大小
	ui->addChild(blood3);//添加精灵节点


	addChild(ui, 4);//参数2指要添加的Zorder的值，指的是该成员的层级（也可指深度），

						/*zorder大的成员在zorder小的成员上面，绘制层的顺序, 默 认参数值为0，表示最高优先层导入，

							该值越大表示该层在最后加载（在最高一层），一般背景图层是首先加载，其他元素在加载在背景层上面。

							因为背景在后面加载的话，会覆盖掉前面加载的元素，看不到想要的图层组合效果。*/


	//初始化猪脚的子弹

	bullets = Array::createWithCapacity(5);
	for (int i = 0; i < bullets->capacity(); i++)
	{
		auto mybullet = new GameHeroBullet();
		mybullet->setIsNotVisable();
		mybullet->setScale(0.5);
		bullets->addObject(mybullet);
		this->addChild(mybullet, 3);

	}
	bullets->retain();


	//初始化敌人的子弹
	enemybullets = Array::createWithCapacity(10);

	for (int i = 0; i < enemybullets->capacity(); i++)
	{
		auto e_bullet = new GameEnemyBullet();
		e_bullet->setIsNotVisable();
		e_bullet->setScale(0.5);

		enemybullets->addObject(e_bullet);

		this->addChild(e_bullet, 3);

	}

	gamemark = new GameMark();
	addChild(gamemark, 4);
	enemybullets->retain();

	//初始化游戏结束画面及按钮
	gameover = Sprite::create("Game11_1/gameover.png");
	gameover->setAnchorPoint(ccp(0.5, 0.5));
	gameover->setPosition(ccp(0, 0));
	gameover->setPosition(ccp(size.width / 2, size.height / 2 + 70));
	gameover->setVisible(false);
	gameover->setScale(0.5);
	addChild(gameover, 5);

	auto pCloseItem = MenuItemImage::create("Game11_1/back.png", "Game11_1/back.png", this, menu_selector(GameMain::menuBackCallback));

	pCloseItem->setPosition(ccp(size.width / 2, size.height / 2 - 50));
	pCloseItem->setScale(0.5);

	auto pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 5, 25);
	pMenu->setVisible(false);
	pMenu->setEnabled(false);

	isreduce = false;
	isover = false;

	//调用此函数，然后重写update函数便可以在游戏循环中控制逻辑
	scheduleUpdate();
	return true;

}

void GameMain::update(float time)
{
	//本函数需要做以下的几件事
	//A.background move
	//B.the dection of collision bettween hero and enemy
	//C.the dection of collision for bullet bettween hero and enemy 
	//

	//背景移动逻辑
	bg1->setPosition(ccp(bg1->getPosition().x, bg1->getPosition().y - 2));
	bg2->setPosition(ccp(bg2->getPosition().x, bg2->getPosition().y - 2));

	if (bg2->getPosition().y < 0)
	{
		float temp = bg2->getPosition().y + 480;

		bg1->setPosition(ccp(bg2->getPosition().x, temp));

	}

	if (bg1->getPosition().y < 0)
	{
		float temp = bg1->getPosition().y + 480;

		bg2->setPosition(ccp(bg1->getPosition().x, temp));

	}

	auto hpos = hero->getPosition();
	//敌人和猪脚子弹的碰撞检测
	for (int i = 0; i < 3; i++)
	{
		GameObjEnemy  *enemy = ((GameObjEnemy*)enemys->objectAtIndex(i));

		auto epos = enemy->getPosition();

		if (enemy->islife)
		{
			for (size_t i = 0; i < bullets->capacity(); i++)
			{
				if (((GameHeroBullet*)bullets->objectAtIndex(i))->getIsvisable())
				{
					if (isCollion(((GameHeroBullet*)bullets->objectAtIndex(i))->getPosition(),
						epos, 5, 13, 21, 28))
					{

						enemy->setdie();
						gamemark->addnumber(200);
						break;
					}
				}

			}
		}
	}

		//敌人和猪脚的碰撞检测
		if (!isreduce && enemy->islife && isCollion(hpos, epos, 21, 22.5, 21, 28))
		{
			enemy->setdie();
			setherohurt();

		}

		//猪脚和敌人子弹的碰撞检测
		if (!isreduce)
		{
			for (size_t i = 0; i < enemybullets->capacity(); i++)
			{
				if (isCollion(hpos, ((GameEnemyBullet*)enemybullets->objectAtIndex(i))->
					getPosition(), 21, 22.5, 5, 13))
				{
					setherohurt();

				}

			}
		}
}


Scene* GameMain::scene()
{
	//创建场景
	auto scene = Scene::create();

	//创建层 新建GameMain对象
	auto layer = GameMain::create();//头文件中CREATE_FUNC(GameMain);宏添加的静态函数，自动调用init()

	//添加层
	scene->addChild(layer);

	return scene;


}

void GameMain::menuBackCallback(cocos2d::Ref* pSender)
{

	Director::sharedDirector()->replaceScene(GameMenu::scene());//调用菜单类
	

}

void GameMain::setherohurt()
{
	//猪脚受伤，减血
	hero->stopAllActions();

	switch (blood)
	{

			case 3:

				blood1->setVisible(false);
				blood--;

				break;

			case 2:

				blood2->setVisible(false);
				blood--;
		
				break;

			case 1:

				blood3->setVisible(false);
				blood--;
				break;

			case 0:

				if (!isover)
				{
					isover = true;
					setover();
				}

				break;


	}

	auto action = Blink::create(5, 10);

	hero->runAction(action);
	schedule(schedule_selector(GameMain::resetreduce), 5.0f);

	isreduce = true;






}
