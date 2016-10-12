#include "OpenScreenScene.h"
#include "GameMenuScene.h"

Scene* COpenScreenScene::createOpenScreenScene()
{
	auto scene = Scene::create();
	auto layer = COpenScreenScene::create();
	scene->addChild(layer);
	return scene;
}

bool COpenScreenScene::init()
{
	if (!LayerColor::initWithColor(Color4B::ORANGE))
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initMoveSprite();
	scheduleOnce(schedule_selector(COpenScreenScene::startMoveSprite), ONE_SECOND);
	return true;
}

void COpenScreenScene::moveKeSpriteToLeft()
{
	MoveBy* pMove_Ch_1_toLeft = MoveBy::create(MOVE_SPLEED, ccp(-spriteSize.width, 0));
	if (pMove_Ch_1_toLeft != NULL)
		pch_1_Sprite->runAction(pMove_Ch_1_toLeft);

	MoveBy* pMove_Ch_3_toLeft = MoveBy::create(MOVE_SPLEED, ccp(spriteSize.width, 0));
	CallFunc* pCall_ch_3_Func = CallFunc::create(CC_CALLBACK_0(COpenScreenScene::moveMaiSpriteToLeft, this));
	if (pMove_Ch_3_toLeft != NULL && pCall_ch_3_Func != NULL)
	{
		pch_3_Sprite->runAction(Sequence::create(pMove_Ch_3_toLeft, pCall_ch_3_Func, NULL));
	}
}

void COpenScreenScene::moveMaiSpriteToLeft()
{
	MoveBy* pMove_Ch_1_toLeft = MoveBy::create(MOVE_SPLEED, ccp(-spriteSize.width, 0));
	if (pMove_Ch_1_toLeft != NULL)
		pch_1_Sprite->runAction(pMove_Ch_1_toLeft);

	MoveBy* pMove_Ch_2_toLeft = MoveBy::create(MOVE_SPLEED, ccp(spriteSize.width, 0));
	CallFunc* pCall_ch_2_Func = CallFunc::create(CC_CALLBACK_0(COpenScreenScene::spriteFadeOut, this));
	if (pMove_Ch_2_toLeft != NULL && pCall_ch_2_Func != NULL)
	{
		pch_2_Sprite->runAction(Sequence::create(pMove_Ch_2_toLeft, pCall_ch_2_Func, NULL));
	}
}

void COpenScreenScene::initMoveSprite()
{
	pch_1_Sprite = Sprite::create(CH_1_IMAGE);
	pch_2_Sprite = Sprite::create(CH_2_IMAGE);
	pch_3_Sprite = Sprite::create(CH_3_IMAGE);
	pch_4_Sprite = Sprite::create(CH_4_IMAGE);

	spriteSize = pch_2_Sprite->getContentSize();

	pch_1_Sprite->setPosition(
								ccp(visibleSize.width/2	+ spriteSize.width,
								visibleSize.height/2)
								
							);

	pch_2_Sprite->setPosition(
								ccp(visibleSize.width / 2 - 2*spriteSize.width,
								visibleSize.height / 2)
							);

	pch_3_Sprite->setPosition(
								ccp(visibleSize.width / 2 - spriteSize.width,
								visibleSize.height / 2)
							);

	pch_4_Sprite->setPosition(
								ccp(visibleSize.width / 2,
								visibleSize.height / 2)
							);

	pch_1_Sprite->setAnchorPoint(ccp(0,	0.5));
	pch_2_Sprite->setAnchorPoint(ccp(0, 0.5));
	pch_3_Sprite->setAnchorPoint(ccp(0, 0.5));
	pch_4_Sprite->setAnchorPoint(ccp(0, 0.5));

	addChild(pch_1_Sprite);
	addChild(pch_2_Sprite);
	addChild(pch_3_Sprite);
	addChild(pch_4_Sprite);
}

void COpenScreenScene::startMoveSprite(float dt)
{
	MoveBy* pMove_Ch_1_toLeft = MoveBy::create(MOVE_SPLEED, ccp(-spriteSize.width, 0));
	if (pMove_Ch_1_toLeft != NULL)
	{
		pch_1_Sprite->runAction(pMove_Ch_1_toLeft);
	}

	MoveBy* pMove_Ch_4_toLeft = MoveBy::create(MOVE_SPLEED, ccp(spriteSize.width, 0));
	CallFunc* pCallFunc = CallFunc::create(CC_CALLBACK_0(COpenScreenScene::moveKeSpriteToLeft, this));
	if (pMove_Ch_4_toLeft != NULL && pCallFunc != NULL)
	{
		pch_4_Sprite->runAction(Sequence::create(pMove_Ch_4_toLeft, pCallFunc, NULL));
	}
}

void COpenScreenScene::gotoMenuScene()
{
	CCLOG("go to next scene ---- CGameMenuScene ");
	TransitionShrinkGrow* pShrinkGrow = TransitionShrinkGrow::create(2.0f, CGameMenuScene::createMenuScene());
	if (pShrinkGrow == NULL)
	{
		return;
	}
	Director::getInstance()->replaceScene(pShrinkGrow);
}

void COpenScreenScene::spriteFadeOut()
{
	FadeOut* pCh_1_Out = FadeOut::create(ONE_SECOND * 2);
	FadeOut* pCh_2_Out = FadeOut::create(ONE_SECOND * 2);
	FadeOut* pCh_3_Out = FadeOut::create(ONE_SECOND * 2);
	FadeOut* pCh_4_Out = FadeOut::create(ONE_SECOND * 2);

	pch_2_Sprite->runAction(pCh_2_Out);
	pch_3_Sprite->runAction(pCh_3_Out);
	pch_4_Sprite->runAction(pCh_4_Out);

	CallFunc* pStartMenu = CallFunc::create(CC_CALLBACK_0(COpenScreenScene::gotoMenuScene, this));
	if (pStartMenu != NULL)
	{
		pch_1_Sprite->runAction(Sequence::create(pCh_1_Out, pStartMenu, NULL));
	}
}
