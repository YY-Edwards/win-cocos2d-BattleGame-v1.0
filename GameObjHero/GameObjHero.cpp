#include "GameObjHero.h"
#include "GameMain\GameMain.h"

void GameObjHero::onEnter()
{
	//CCNode::onEnter();
	Node::onEnter();

	this->setContentSize(CCSizeMake(85, 90));//跟触摸有关

	// Adds Touch Event Listener
	//单点触摸
	auto listener = EventListenerTouchOneByOne::create();
	//设置吞噬为true,不让触摸往下传递
	listener->setSwallowTouches(true);

	//和回调函数绑定
	listener->onTouchBegan = CC_CALLBACK_2(GameObjHero::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameObjHero::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameObjHero::onTouchEnded, this);

	//添加监听器到事件分发器中
	//另外，有一点非常重要，FixedPriority listener添加完成之后需要手动remove，
	//而SceneGraphPriority listener是跟node绑定的，在node的析构函数中会被移除。
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//这里需要注意使用的函数
	_touchListener = listener;

	auto mainsprite = Sprite::create("Game11_1/catBody1.png");

	//主体动画
	auto animation = Animation::create();
	animation->addSpriteFrameWithFileName("Game11_1/catBody1.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody3.png");
	animation->addSpriteFrameWithFileName("Game11_1/catBody2.png");

	animation->setDelayPerUnit(0.1f);//总时间，以秒为单位。
	animation->setRestoreOriginalFrame(true);//动画结束时恢复至初始帧
	mainsprite->runAction(RepeatForever::create(Animate::create(animation)));

	this->addChild(mainsprite);

	//尾巴
	auto tail = Sprite::create("Game11_1/catTail.png");
	tail->setAnchorPoint(ccp(0.5, 1));
	tail->setPosition(ccp(-5, -29));
	tail->setScale(0.5);
	tail->setRotation(20);
	//左右摇摆
	tail->runAction(RepeatForever::create((ActionInterval*)Sequence::
		create(RotateBy::create(0.5, -40), RotateBy::create(0.5, 40), NULL)));
	this->addChild(tail);

	//zuo手
	lefthand = Sprite::create("Game11_1/catHandl.png");
	lefthand->setAnchorPoint(ccp(1, 0.5));
	lefthand->setPosition(ccp(-18, -20));
	this->addChild(lefthand);

	//you手
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
	
	//获取精灵对象并取得精灵的矩阵
	//auto sprite = static_cast<Sprite*>(event->getCurrentTarget());

	//Rect rect = sprite->getBoundingBox();

	//获取触摸点的坐标

	//auto point = touch->getLocation();

	
	if (((GameMain *)this->getParent())->isover)//判断猪脚是否已阵亡
		return false;


	if (!containsTouchLocation(touch)){//判断触摸点是否在猪脚的矩形框中

		return false;
	}
	else{

		//获得触摸偏移位置
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

void GameObjHero::onTouchEnded(Touch* touch, Event* event)
{
	//触摸结束时，需要将猪脚的两只手放下并且将iscontol置为false.

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
	//释放子弹
	if (iscontrol)
	{
		auto pos = this->getPosition();

		auto p = (GameMain*)this->getParent();

		p->releaseheroBullet(pos.x, pos.y + 30);


	}


}

