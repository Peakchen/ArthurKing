#include "FloatingHead.h"


CFloatingHead::CFloatingHead()
{
}


CFloatingHead::~CFloatingHead()
{
}

void CFloatingHead::createFloatingHead(Node *pNode, const std::string szMsg, float itimes, Vec2 oPoint)
{
	// 飘字内容 
	auto oMsgLable = Label::createWithSystemFont(szMsg, "Arial", 15);
	oMsgLable->setColor(Color3B::WHITE);
	oMsgLable->ignoreAnchorPointForPosition(false);
	oMsgLable->setTag(EFloatMsg_Label);
	oMsgLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	
	// 飘字 节点 layer 层
	auto oMsglayer = LayerColor::create(Color4B(0, 0, 0, 255));
	oMsglayer->ignoreAnchorPointForPosition(false);
	oMsglayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	oMsglayer->setTag(EFloatMsg_Layer);
	oMsglayer->setContentSize(oMsgLable->getContentSize() + Size(20, 15));

	if (pNode == NULL)
	{
		return;
	}

	pNode->addChild(oMsglayer);
	pNode->addChild(oMsgLable);

	oMsglayer->setPosition(oPoint);
	oMsgLable->setPosition(oMsglayer->getPosition());

	Vec2 upVec = Vec2(oMsglayer->getPosition().x + 50, oMsglayer->getPosition().y);
	Vec2 downVec = Vec2(oMsglayer->getPosition().x - 50, oMsglayer->getPosition().y);

	if (itimes <= 0 )
	{
		CCLOG("error： 延时不能为 %d...", itimes);
		return;
	}

	FadeIn* pBeginIn = FadeIn::create(itimes/5);
	if (pBeginIn == NULL)
	{
		CCLOG("error： 淡入 出错...");
		return;
	}

	DelayTime* pDelaytime = DelayTime::create(itimes / 5 * 1.5);
	if (pDelaytime == NULL)
	{
		CCLOG("error： 延时出错...");
		return;
	}

	FadeOut* pBeginOut = FadeOut::create(itimes / 5 * 2.5);
	if (pBeginOut == NULL)
	{
		CCLOG("error： 淡出 出错...");
		return;
	}

	auto down2Up = Sequence::create(pBeginIn,
									pDelaytime,
									pBeginOut,
									CallFuncN::create(pNode, callfuncN_selector(CFloatingHead::removeFloatingHead)),
									NULL
									);

	EaseBackIn* pEndEaseBack = EaseBackIn::create(MoveBy::create(itimes / 5, Vec2(0, 50)));
	if (pEndEaseBack == NULL)
	{
		CCLOG("error: pEndEaseBack create fail...");
		return;
	}
	auto Up2Down = Sequence::create(pEndEaseBack,
									DelayTime::create(itimes/5*2),
									EaseBackOut::create(MoveBy::create(itimes / 5 * 2, Vec2(0, 25))),
									NULL
									);

	auto pSpwan = Spawn::create(down2Up, Up2Down, NULL);
	auto pRepate = Repeat::create(pSpwan, 1);
	
	// 设置消失
	oMsgLable->setOpacity(0);
	oMsglayer->setOpacity(0);

	oMsglayer->runAction(pRepate);
	oMsgLable->runAction(pRepate->clone());
}

void CFloatingHead::removeFloatingHead(Node *node)
{
	node->removeChildByTag(EFloatMsg_Label);
	node->removeChildByTag(EFloatMsg_Layer);
	//this->removeFromParent();
	//this->removeFromParentAndCleanup(true);
}
