#include "GameObjHero.h"
#include "GameMain\GameMain.h"

void GameObjHero::onEnter()
{
	//CCNode::onEnter();
	Node::onEnter();

	this->setContentSize(CCSizeMake(85, 90));//�������й�

	// Adds Touch Event Listener
	//���㴥��
	auto listener = EventListenerTouchOneByOne::create();
	//��������Ϊtrue,���ô������´���
	listener->setSwallowTouches(true);

	//�ͻص�������
	listener->onTouchBegan = CC_CALLBACK_2(GameObjHero::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameObjHero::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameObjHero::onTouchEnded, this);

	//��Ӽ��������¼��ַ�����
	//���⣬��һ��ǳ���Ҫ��FixedPriority listener������֮����Ҫ�ֶ�remove��
	//��SceneGraphPriority listener�Ǹ�node�󶨵ģ���node�����������лᱻ�Ƴ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//������Ҫע��ʹ�õĺ���
	_touchListener = listener;

	auto mainsprite = Sprite::create("Game11_1/catBody1.png");

	//���嶯��
	auto animation = Animation::create();
	animation->addSpriteFrameWithFileName("Game11_1/catBody1.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody3.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");

	animation->setDelayPerUnit(0.1f);//��ʱ�䣬����Ϊ��λ��
	animation->setRestoreOriginalFrame(true);//��������ʱ�ָ�����ʼ֡
	mainsprite->runAction(RepeatForever::create(Animate::create(animation)));

	this->addChild(mainsprite);

	//β��
	auto tail = Sprite::create("Game11_1/catTail.png");
	tail->setAnchorPoint(ccp(0.5, 1));
	tail->setPosition(ccp(-5, -29));
	tail->setScale(0.5);
	tail->setRotation(20);
	//����ҡ��
	tail->runAction(RepeatForever::create((ActionInterval*)Sequence::
		create(RotateBy::create(0.5, -40), RotateBy::create(0.5, 40), NULL)));
	this->addChild(tail);

	//zuo��
	lefthand = Sprite::create("Game11_1/catHandl.png");
	lefthand->setAnchorPoint(ccp(1, 0.5));
	lefthand->setPosition(ccp(-18, -20));
	this->addChild(lefthand);

	//you��
	righthand = Sprite::create("Game11_1/catHandr.png");
	righthand->setAnchorPoint(ccp(0, 0.5));
	righthand->setPosition(ccp(18, -20));
	this->addChild(righthand);

	offset = ccp(0, 0);
	iscontrol = false;

	schedule(schedule_selector(GameObjHero::releasebullet), 1.0f);



}

void GameObjHero::onExit()
{
	//auto pDirector = Director::getInstance();

	Node::onExit();


}

bool GameObjHero::onTouchBegan(Touch* touch, Event* event)
{
	
	//��ȡ�������ȡ�þ���ľ���
	//auto sprite = static_cast<Sprite*>(event->getCurrentTarget());

	//Rect rect = sprite->getBoundingBox();

	//��ȡ�����������

	//auto point = touch->getLocation();

	
	if (((GameMain *)this->getParent())->isover)//�ж�����Ƿ�������
		return false;


	if (!containsTouchLocation(touch)){//�жϴ������Ƿ�����ŵľ��ο���

		return false;
	}
	else{

		//��ô���ƫ��λ��
		iscontrol = true;
		auto touchPoint = touch->getLocationInView();
		//touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
		touchPoint = Director::getInstance()->convertToGL(touchPoint);

		offset.x = touchPoint.x - this->getPosition().x;
		offset.y = touchPoint.y - this->getPosition().y;

	}

	return true;

}

void GameObjHero::onTouchMoved(Touch* touch, Event* event)
{
	if (iscontrol){
		auto touchPoint = touch->getLocationInView();
		//touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
		touchPoint = Director::getInstance()->convertToGL(touchPoint);

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

void GameObjHero::onTouchEnded(Touch* touch, Event* event)
{
	//��������ʱ����Ҫ����ŵ���ֻ�ַ��²��ҽ�iscontol��Ϊfalse.

	if (iscontrol)
	{
		iscontrol = false;

		lefthand->setFlipY(false);
		righthand->setFlipY(false);
	}

	CCLOG(" \r\n Touch-End	\r\n");
}

bool GameObjHero::containsTouchLocation(Touch* touch)
{
	
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));

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

Rect GameObjHero::rect()
{
	auto s = CCSizeMake(85, 90);

	return CCRectMake(-s.width / 2, -s.height, s.width, s.height);


}

void GameObjHero::releasebullet(float dt)
{
	//�ͷ��ӵ�
	if (iscontrol)
	{
		auto pos = this->getPosition();

		auto p = (GameMain*)this->getParent();

		p->releaseheroBullet(pos.x, pos.y + 30);


	}


}

