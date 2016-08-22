#include "GameMain.h"



bool GameMain::init()
{
	//�ȵ��ø���
	if (!Layer::init())
	{

		return false;
	}

	//���ݵ�һ�γ��֣���ȡ��Ļ��С
	Size size = Director::sharedDirector()->getWinSize();

	//��������
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

	//�������

	hero = new GameObjHero();
	hero->setPosition(ccp(size.width / 2, -50));
	hero->setScale(0.5);
	addChild(hero, 2, 1);
	hero->runAction(MoveBy::create(0.5, ccp(0, 150)));

	//��������
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

	//����Ѫ��UI
	blood = 3;
	//���������
	auto ui = SpriteBatchNode::create("Game11_1/cat.png");

	blood1 = Sprite::createWithTexture(ui->getTexture());
	blood1->setPosition(ccp(20, size.height - 20));
	blood1->setScale(0.2);
	ui->addChild(blood1);////child����ڵ����У���Ĭ��ZOrderֵΪ0.���������Ӽ����
						//��һ���������еĽڵ㣬onEnter������onEnterTransitionDidFinish�������ᱻ���á�

	blood2 = Sprite::createWithTexture(ui->getTexture());
	blood2->setPosition(ccp(50, size.height - 20));
	blood2->setScale(0.2);
	ui->addChild(blood2);

	blood3 = Sprite::createWithTexture(ui->getTexture());//������ͼ����
	blood3->setPosition(ccp(80, size.height - 20));//����λ��
	blood3->setScale(0.2);//������Դ���ź��ʴ�С
	ui->addChild(blood3);//��Ӿ���ڵ�


	addChild(ui, 4);//����2ָҪ��ӵ�Zorder��ֵ��ָ���Ǹó�Ա�Ĳ㼶��Ҳ��ָ��ȣ���

						/*zorder��ĳ�Ա��zorderС�ĳ�Ա���棬���Ʋ��˳��, Ĭ �ϲ���ֵΪ0����ʾ������Ȳ㵼�룬

							��ֵԽ���ʾ�ò��������أ������һ�㣩��һ�㱳��ͼ�������ȼ��أ�����Ԫ���ڼ����ڱ��������档

							��Ϊ�����ں�����صĻ����Ḳ�ǵ�ǰ����ص�Ԫ�أ���������Ҫ��ͼ�����Ч����*/


	//��ʼ����ŵ��ӵ�

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


	//��ʼ�����˵��ӵ�
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

	//��ʼ����Ϸ�������漰��ť
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

	//���ô˺�����Ȼ����дupdate�������������Ϸѭ���п����߼�
	scheduleUpdate();
	return true;

}

void GameMain::update(float time)
{
	//��������Ҫ�����µļ�����
	//A.background move
	//B.the dection of collision bettween hero and enemy
	//C.the dection of collision for bullet bettween hero and enemy 
	//

	//�����ƶ��߼�
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
	//���˺�����ӵ�����ײ���
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

		//���˺���ŵ���ײ���
		if (!isreduce && enemy->islife && isCollion(hpos, epos, 21, 22.5, 21, 28))
		{
			enemy->setdie();
			setherohurt();

		}

		//��ź͵����ӵ�����ײ���
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
	//��������
	auto scene = Scene::create();

	//������ �½�GameMain����
	auto layer = GameMain::create();//ͷ�ļ���CREATE_FUNC(GameMain);����ӵľ�̬�������Զ�����init()

	//��Ӳ�
	scene->addChild(layer);

	return scene;


}

void GameMain::menuBackCallback(cocos2d::Ref* pSender)
{

	Director::sharedDirector()->replaceScene(GameMenu::scene());//���ò˵���
	

}

void GameMain::setherohurt()
{
	//������ˣ���Ѫ
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
