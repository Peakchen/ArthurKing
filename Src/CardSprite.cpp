#include "CardSprite.h"
#include "MapReader.h"
#include "AIPersonMessageMacro.h"
#include "ResCreator.h"


CCardSprite::CCardSprite()
{
	m_RandNum = 0;
	m_pArthur = NULL;

}


CCardSprite::~CCardSprite()
{
}

CCardSprite* CCardSprite::create(const char* strInCard, const char* strOutCard, float fDuration)
{
	CCardSprite* pCardSprite = new CCardSprite();
	if (pCardSprite && pCardSprite->init(strInCard, strOutCard, fDuration))
	{
		pCardSprite->autorelease();
		return pCardSprite;
	}

	CC_SAFE_DELETE(pCardSprite);
	return NULL;
}

bool CCardSprite::init(const char* strInCard, const char* strOutCard, float fDuration)
{
	if (!Sprite::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	initCardData(strInCard, strOutCard, fDuration);
	return true;
}

void CCardSprite::initCardData(const char* strInCard, const char* strOutCard, float fDuration)
{

	m_isOpen = false;		// 初始化 未翻开

	if (getChildByTag(EOutCard))
	{
		removeChildByTag(EOutCard);
	}
	
	if (getChildByTag(EOutCard))
	{
		removeChildByTag(EInCard);
	}
	
	Scale9Sprite* pBtn_NormalSprite = Scale9Sprite::create(strOutCard);
	Scale9Sprite* pBtn_PressSprite = Scale9Sprite::create(strOutCard);
	if (pBtn_NormalSprite == NULL)
	{
		CCLOG(" pBtn_NormalSprite 非法九宫格精灵.");
		return;
	}

	if (pBtn_PressSprite == NULL)
	{
		CCLOG(" pBtn_PressSprite 非法九宫格精灵.");
		return;
	}

	LabelTTF* pbtn_LabelTTF = LabelTTF::create("", "Marker Felt", 20);
	if (pbtn_LabelTTF == NULL)
	{
		CCLOG(" pbtn_LabelTTF 非法九宫格精灵.");
		return;
	}

	ControlButton* pCtrl_Btn = ControlButton::create(pbtn_LabelTTF, pBtn_NormalSprite);
	if (pCtrl_Btn == NULL)
	{
		CCLOG(" pCtrl_Btn 非法九宫格精灵.");
		return;
	}
	pCtrl_Btn->setBackgroundSpriteForState(pBtn_PressSprite, Control::State::SELECTED);

	pCtrl_Btn->setPosition(ccp(visibleSize.width / 2 - 220, visibleSize.height - 80));
	pCtrl_Btn->setPreferredSize(Size(128, 128));
	pCtrl_Btn->addTargetWithActionForControlEvents(this, cccontrol_selector(CCardSprite::GameChangeTouchDown), Control::EventType::TOUCH_DOWN);
	pCtrl_Btn->setTag(EOutCard);
	pCtrl_Btn->setVisible(true);
	addChild(pCtrl_Btn);

	// in card
	Sprite* pInCard = Sprite::create(strInCard);
	if (pInCard == NULL)
	{
		CCLOG("error: 创建 pInCard 非法.");
		return;
	}
	pInCard->setPosition(ccp(visibleSize.width / 2 - 220, visibleSize.height - 80));
	pInCard->setVisible(false);	  // hide 
	pInCard->setTag(EInCard);
	addChild(pInCard);

}

void CCardSprite::DoOpenCard()
{
	ControlButton* pInCard = static_cast<ControlButton*>(getChildByTag(EInCard));
	if (pInCard)
	{
		CCLOG("error: %s 创建 pOutCard 非法.", __FUNCTION__);
		pInCard->runAction(m_pAnimInOpen);
	}
	Sprite* pOutCard = static_cast<Sprite*>(getChildByTag(EOutCard));
	if (pOutCard)
	{
		CCLOG("error: %s 创建 pOutCard 非法.", __FUNCTION__);
		pOutCard->runAction(m_pAnimOutOpen);
	}

}

void CCardSprite::GameChangeTouchDown(Object* pSender, Control::EventType event)
{
	CCSequence* pSequenceIn = CCSequence::create(
		CCDelayTime::create(0.5f), 
		CCShow::create(), 
		CCDelayTime::create(3.5f), 
		CCHide::create(), 
		NULL
		);

	CCOrbitCamera* pInCamera = CCOrbitCamera::create(5.0f, 1.0f, 0.0f, ECardAngleIn, ECardAngleDelta, 0.0f, 0.0f);
	if (pSequenceIn == NULL || pInCamera == NULL)
	{
		return;
	}
	m_pAnimInOpen = CCSpawn::create(pSequenceIn, pInCamera, NULL);

	pCallFunc_AfterOpen = CallFunc::create(CC_CALLBACK_0(CCardSprite::OnAfterOpenCard_FireEvent, this));

	CCSequence* pSequenceOut = CCSequence::create(
		CCDelayTime::create(0.5f),
		CCHide::create(),
		CCDelayTime::create(3.5f),
		pCallFunc_AfterOpen,
		NULL
		);

	CCOrbitCamera* pOutCamera = CCOrbitCamera::create(5.0f, 1.0f, 0.0f, ECardAngleOut, -360, 0.0f, 0.0f);
	if (pSequenceOut == NULL || pOutCamera == NULL)
	{
		return;
	}
	m_pAnimOutOpen = CCSpawn::create(pOutCamera, pSequenceOut, NULL);

	Sprite* pInCard = static_cast<Sprite*>(getChildByTag(EInCard));
	if (pInCard)
	{
		pInCard->runAction(m_pAnimInOpen);
	}

	ControlButton* pOutCard = static_cast< ControlButton* >( getChildByTag(EOutCard) );
	if (pOutCard)
	{
		pOutCard->runAction(m_pAnimOutOpen);
	}
}

bool CCardSprite::__CheckCardSpriteLoad()
{
	return true;
}

void CCardSprite::OnAfterOpenCard_FireEvent()
{
	g_ResCreator.GetPersonMessageInstance()->FireMessage(OpenCard_Action, "Open Card Action");
}

