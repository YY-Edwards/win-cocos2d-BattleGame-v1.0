#include "GameObjHero.h"

void GameObjHero::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(85, 90));

	// Adds Touch Event Listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameObjHero::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameObjHero::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameObjHero::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener, -10);
	_touchListener = listener;

	auto mainsprite = CCSprite::create("Game11_1/catBody1.png");

	//主体动画
	auto animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("Game11_1/catBody1.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody3.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");

	animation->setDelayPerUnit(0.1f);//总时间，以秒为单位。
	animation->setRestoreOriginalFrame(true);//动画结束时恢复至初始帧
	mainsprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	addChild(mainsprite);

	//尾巴
	auto tail = CCSprite::create("Game11_1/catTail.png");
	tail->setAnchorPoint(ccp(0.5, 1));
	tail->setPosition(ccp(-5, -29));
	tail->setScale(0.5);
	tail->setRotation(20);
	//左右摇摆
	tail->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::
		create(CCRotateBy::create(0.5, -40), CCRotateBy::create(0.5, 40), NULL)));
	addChild(tail);

	//手
	lefthand = CCSprite::create("Game11_1/catHand1.png");
	lefthand->setAnchorPoint(ccp(1, 0.5));
	lefthand->setPosition(ccp(-18, -20));
	addChild(lefthand);

	righthand = CCSprite::create("Game11_1/catHand2.png");
	righthand->setAnchorPoint(ccp(18, -20));
	righthand->setPosition(ccp(0, 0.5));
	addChild(righthand);

	offset = ccp(0, 0);
	iscontrol = false;

	schedule(schedule_selector(GameObjHero::releasebullet), 1.0f);



}


bool GameObjHero::onTouchBegan(CCTouch* touch, CCEvent* event)
{
	if ((GameMain *)this->getParent()->isover)//判断猪脚是否已阵亡
		return false;
	if (!containsTouchLocation(touch)){//判断触摸点是否在猪脚的矩形框中

		return false;
	}
	else{

		//获得触摸偏移位置
		iscontrol = true;
		auto touchPoint = touch->getLocationInView();
		touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
		offset.x = touchPoint.x - this->getPosition().x;
		offset.y = touchPoint.y - this->getPosition().y;

	}

	return true;

}

bool GameObjHero::onTouchMoved(CCTouch* touch, CCEvent* event)
{
	if (iscontrol){
		auto touchPoint = touch->getLocationInView();
		touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

		//设置左右手上下
		//通过偏移位置和触摸点移动过后的位置计算出猪脚现在的坐标点
		float x = touchPoint.x - offset.x;

		float y = touchPoint.y - offset.y;

		//下一个坐标点的位置的横坐标大于目前坐标的位置的横坐标，
		//说明猪脚是在向右移动，则右手抬起。反之亦然
		if (x < this->getPosition().x)
		{
			//抬起：Y轴反转即是Y轴镜像
			lefthand->setFlipY(true);
			righthand->setFlipY(false);
		}
		else{
			
			lefthand->setFlipY(false);
			righthand->setFlipY(true);

		}

		this->setPosition(x, y);


	}


}

bool GameObjHero::onTouchEnded(CCTouch* touch, CCEvent* event)
{
	//触摸结束时，需要将猪脚的两只手放下并且将iscontol置为false.

	if (iscontrol)
	{
		iscontrol = false;

		lefthand->setFlipY(false);
		righthand->setFlipY(false);
	}
}

GameObjHero::GameObjHero()
{
	;
}

GameObjHero::~GameObjHero()
{

	// Removes Touch Event Listener
	_eventDispatcher->removeEventListener(_touchListener);
	//_eventDispatcher->removeEventListener(_keyboardListener);

}



