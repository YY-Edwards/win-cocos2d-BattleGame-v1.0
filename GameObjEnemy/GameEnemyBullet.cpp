#include "GameEnemyBullet.h"

void GameEnemyBullet::onEnter()
{
	CCNode::onEnter();

	//初始化主体

	this->setContentSize(CCSizeMake(21, 52));
	auto mainbody = CCSprite::create("Game11_1/DrDogZD.png");
	mainbody->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
	addChild(mainbody);


}

GameEnemyBullet::GameEnemyBullet()
{
	
	isvisable = false;



}

GameEnemyBullet::~GameEnemyBullet()
{


}

bool GameEnemyBullet::getIsvisable()
{

	return isvisable;

}

void GameEnemyBullet::setIsVisable()
{ 
	//运行动作
	this->setVisible(true);
	isvisable = true;
	this->runAction(RepeatForever::create(RotateBy::create(1, 360)));
	this->runAction(Sequence::create(MoveTo::create((this->getPosition().y + 50) / 150,
		ccp(this->getPosition().x, -50)), CallFuncN::create(this, callfuncN_selector(GameEnemyBullet::setIsNotVisable)), NULL));

}

void GameEnemyBullet::setIsNotVisable(Node* dd)
{
	this->setVisible(false);
	isvisable = false;
	this->stopAllActions();

}


void GameEnemyBullet::onExit()
{
	
	Node::onExit();

}

