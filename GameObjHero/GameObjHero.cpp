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

	//���嶯��
	auto animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("Game11_1/catBody1.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody3.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");

	animation->setDelayPerUnit(0.1f);//��ʱ�䣬����Ϊ��λ��
	animation->setRestoreOriginalFrame(true);//��������ʱ�ָ�����ʼ֡
	mainsprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	addChild(mainsprite);

	//β��
	auto tail = CCSprite::create("Game11_1/catTail.png");
	tail->setAnchorPoint(ccp(0.5, 1));
	tail->setPosition(ccp(-5, -29));
	tail->setScale(0.5);
	tail->setRotation(20);
	//����ҡ��
	tail->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::
		create(CCRotateBy::create(0.5, -40), CCRotateBy::create(0.5, 40), NULL)));
	addChild(tail);

	//��
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
	if ((GameMain *)this->getParent()->isover)//�ж�����Ƿ�������
		return false;
	if (!containsTouchLocation(touch)){//�жϴ������Ƿ�����ŵľ��ο���

		return false;
	}
	else{

		//��ô���ƫ��λ��
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

		//��������������
		//ͨ��ƫ��λ�úʹ������ƶ������λ�ü����������ڵ������
		float x = touchPoint.x - offset.x;

		float y = touchPoint.y - offset.y;

		//��һ��������λ�õĺ��������Ŀǰ�����λ�õĺ����꣬
		//˵��������������ƶ���������̧�𡣷�֮��Ȼ
		if (x < this->getPosition().x)
		{
			//̧��Y�ᷴת����Y�᾵��
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
	//��������ʱ����Ҫ����ŵ���ֻ�ַ��²��ҽ�iscontol��Ϊfalse.

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



