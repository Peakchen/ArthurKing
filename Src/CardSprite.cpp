#include "CardSprite.h"
#include "MapReader.h"


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

	
	m_isOpen = false;		// ��ʼ�� δ����

	Scale9Sprite* pBtn_NormalSprite = Scale9Sprite::create(strOutCard);
	Scale9Sprite* pBtn_PressSprite = Scale9Sprite::create(strOutCard);
	if (pBtn_NormalSprite == NULL)
	{
		CCLOG(" pBtn_NormalSprite �Ƿ��Ź�����.");
		return;
	}

	if (pBtn_PressSprite == NULL)
	{
		CCLOG(" pBtn_PressSprite �Ƿ��Ź�����.");
		return;
	}

	LabelTTF* pbtn_LabelTTF = LabelTTF::create("", "Marker Felt", 20);
	if (pbtn_LabelTTF == NULL)
	{
		CCLOG(" pbtn_LabelTTF �Ƿ��Ź�����.");
		return;
	}

	ControlButton* pCtrl_Btn = ControlButton::create(pbtn_LabelTTF, pBtn_NormalSprite);
	if (pCtrl_Btn == NULL)
	{
		CCLOG(" pCtrl_Btn �Ƿ��Ź�����.");
		return;
	}
	pCtrl_Btn->setBackgroundSpriteForState(pBtn_PressSprite, Control::State::SELECTED);

	pCtrl_Btn->setPosition(ccp(visibleSize.width / 2, visibleSize.height/2));
	pCtrl_Btn->setPreferredSize(Size(128, 128));
	pCtrl_Btn->addTargetWithActionForControlEvents(this, cccontrol_selector(CCardSprite::GameChangeTouchDown), Control::EventType::TOUCH_DOWN);
	pCtrl_Btn->setTag(EOutCard);
	pCtrl_Btn->setVisible(true);
	addChild(pCtrl_Btn);

	// in card
	Sprite* pInCard = Sprite::create(strInCard);
	if (pInCard == NULL)
	{
		CCLOG("error: ���� pInCard �Ƿ�.");
		return;
	}
	pInCard->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	pInCard->setVisible(false);	  // hide 
	pInCard->setTag(EInCard);
	addChild(pInCard);

}

void CCardSprite::DoOpenCard()
{
	ControlButton* pInCard = static_cast<ControlButton*>(getChildByTag(EInCard));
	if (pInCard)
	{
		CCLOG("error: %s ���� pOutCard �Ƿ�.", __FUNCTION__);
		pInCard->runAction(m_pAnimInOpen);
	}
	Sprite* pOutCard = static_cast<Sprite*>(getChildByTag(EOutCard));
	if (pOutCard)
	{
		CCLOG("error: %s ���� pOutCard �Ƿ�.", __FUNCTION__);
		pOutCard->runAction(m_pAnimOutOpen);
	}

}

void CCardSprite::GameChangeTouchDown(Object* pSender, Control::EventType event)
{
	CCSequence* pSequenceIn = CCSequence::create(
		CCDelayTime::create(0.5f), 
		CCShow::create(), 
		CCDelayTime::create(5.5f), 
		CCHide::create(), 
		NULL
		/*CCDelayTime::create(fDuration),
		CCShow::create(),
		NULL*/
		);

	CCOrbitCamera* pInCamera = CCOrbitCamera::create(5.0f, 1.0f, 0.0f, ECardAngleIn, ECardAngleDelta, 0.0f, 0.0f);
	if (pSequenceIn == NULL || pInCamera == NULL)
	{
		return;
	}
	m_pAnimInOpen = CCSpawn::create(pSequenceIn, pInCamera, NULL);


	CCSequence* pSequenceOut = CCSequence::create(
		CCDelayTime::create(0.5f), CCHide::create(), /*CCDelayTime::create(0.5f), CCShow::create(),*/ NULL
		/*CCDelayTime::create(fDuration),
		CCHide::create(),
		NULL*/
		);
	CCOrbitCamera* pOutCamera = CCOrbitCamera::create(5.0f, 1.0f, 0.0f, ECardAngleOut, -360, 0.0f, 0.0f);
	if (pSequenceOut == NULL || pOutCamera == NULL)
	{
		return;
	}
	m_pAnimOutOpen = CCSpawn::create(pOutCamera, pSequenceOut, NULL);

	ControlButton* pOutCard = static_cast<ControlButton*>(getChildByTag(EOutCard));
	if (pOutCard)
	{
		pOutCard->runAction(m_pAnimOutOpen);
	}
	Sprite* pInCard = static_cast<Sprite*>(getChildByTag(EInCard));
	if (pInCard)
	{
		pInCard->runAction(m_pAnimInOpen);
	}


	/*this->removeChildByTag(EOutCard);
	this->removeChildByTag(EInCard);*/
}

bool CCardSprite::__CheckCardSpriteLoad()
{
	return true;
}
