#include "GameEnemyBullet.h"

void GameEnemyBullet::onEnter()
{
	CCNode::onEnter();

	//��ʼ������

	this->setContentSize(CCSizeMake(21, 52));
	auto mainbody = CCSprite::create("Game11_1/DrDogZD.png");
	mainbody->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
	addChild(mainbody);


}
