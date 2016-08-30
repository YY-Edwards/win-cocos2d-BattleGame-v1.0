#include "GameHeroBullet.h"

void GameHeroBullet::onEnter()
{
	CCNode::onEnter();

	//初始化主体

	this->setContentSize(CCSizeMake(21, 52));
	auto mainbody = CCSprite::create("Game11_1/catZD.png");
	mainbody->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
	addChild(mainbody);


}

GameHeroBullet::GameHeroBullet()
{

	isvisable = false;



}

GameHeroBullet::~GameHeroBullet()
{


}

bool GameHeroBullet::getIsvisable()
{

	return isvisable;

}

void GameHeroBullet::setIsVisable()
{
	//运行动作
	this->setVisible(true);
	isvisable = true;
	this->runAction(Sequence::create(MoveTo::create((-this->getPosition().y + 550) / 150,
		ccp(this->getPosition().x, 550)), CallFuncN::create(this, callfuncN_selector(GameHeroBullet::setIsNotVisable)), NULL));

}

void GameHeroBullet::setIsNotVisable(Node* dd )
{
	this->setVisible(false);
	isvisable = false;
	this->stopAllActions();

}


void GameHeroBullet::onExit()
{

	Node::onExit();

}