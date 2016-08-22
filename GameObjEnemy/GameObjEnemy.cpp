#include "GameObjEnemy.h"

void GameObjEnemy::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(99, 111));

     mainbody = CCSprite::create("Game11_1/DrDog1.png");

	//初始化动画
	auto animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("Game11_1/DrDog1.png");
	animation->addSpriteFrameWithFileName("Game11_1/DrDog2.png");

	animation->setDelayPerUnit(0.1f);//总时间，以秒为单位。
	animation->setRestoreOriginalFrame(true);//动画结束时恢复至初始帧
	mainbody->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	addChild(mainbody);

	boom = CCSprite::create("Game11_1/Boom1.png");
	addChild(boom);
	boom->setVisible(false);

	islife = true;


}
void GameObjEnemy::onExit()
{
	Node::onExit();

}
void GameObjEnemy::setType(short var)
{
	type = var;

}


void GameObjEnemy::setdie()
{

	//狗博士处于正常状态时，将爆炸精灵设置为不可见；
	//死亡状态时，主体部分设置为不可见，爆炸可见

	islife = false;
	mainbody->setVisible(false);
	boom->setVisible(true);
	this->stopAllActions();

	//爆炸动画
	auto boomAnimation = CCAnimation::create();
	boomAnimation->addSpriteFrameWithFileName("Game11_1/Boom1.png");
	boomAnimation->addSpriteFrameWithFileName("Game11_1/Boom2.png");
	boomAnimation->addSpriteFrameWithFileName("Game11_1/Boom3.png");
	boomAnimation->addSpriteFrameWithFileName("Game11_1/Boom4.png");
	boomAnimation->addSpriteFrameWithFileName("Game11_1/Boom5.png");
	boomAnimation->setDelayPerUnit(0.1f);//总时间，以秒为单位。
	boomAnimation->setRestoreOriginalFrame(true);//动画结束时恢复至初始帧

	//运行爆炸动画之后，会重新开始调用函数restart.
	boom->runAction(CCSequence::create(CCAnimate::
		create(boomAnimation), CCCallFunc::create(this, callfuncN_selector(GameObjEnemy::restart)), NULL));


}

void GameObjEnemy::restart()
{
	mainbody->setVisible(true);
	boom->setVisible(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->setPosition(ccp(size.width / 4 * type, size.height + 50));

	islife = true;

	mainbody->setVisible(true);
	boom->setVisible(false);
	this->movestart();


}

void GameObjEnemy::movestart()
{
	islife = true;
	int type = CCRANDOM_0_1() * 4;// CCRANDOM_0_1() 取值范围是[0,1]

	//贝塞尔曲线移动
	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = CCPointMake(this->getPosition().x - 400, 330);
	bezier2.controlPoint_2 = CCPointMake(this->getPosition().x + 400, 280);
	bezier2.endPosition = CCPointMake(this->getPosition().x , - 70);
	
	auto bezierBy2 = CCBezierTo::create(6, bezier2);

	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = CCPointMake(this->getPosition().x + 400, 330);
	bezier1.controlPoint_2 = CCPointMake(this->getPosition().x - 400, 280);
	bezier1.endPosition = CCPointMake(this->getPosition().x , - 70);

	auto bezierBy2 = CCBezierTo::create(6, bezier1);


	//设置三种移动方式，两种曲线移动方式和一种直线移动方式。
	switch (type)
	{

	case 0:
	case 1:

		this->runAction(CCSequence::create(CCMoveBy::create(6, ccp(0, -600)),
			CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::restart)), NULL));
		break;

	case 2:

		this->runAction(CCSequence::create(bezierBy2,
			CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::restart)), NULL));

		break;

	case 3:

		this->runAction(CCSequence::create(bezierBy1,
			CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::restart)), NULL));

		break;

	}

	schedule(schedule_selector(GameObjEnemy::releasebullet), 1.2f);//边移动边释放子弹


}
