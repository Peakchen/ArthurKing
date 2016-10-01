#include "RockerAction.h"
#include <math.h>
#include "MacroDefine.h"


CRockerAction::CRockerAction()
{
	m_bPersonRunDirection = false;
	m_pEventDispatcher = NULL;
	m_pEventTouchListener = NULL;
}


CRockerAction::~CRockerAction()
{
	// 程序结束，删除监听
	m_pEventDispatcher->removeEventListener(m_pEventTouchListener);
}

CRockerAction* CRockerAction::CreateRockerEntity(const char* strRockerImageName, const char* strRockerImageBgName, cocos2d::CCPoint stPoint)
{
	CRockerAction* pRockerAction = CRockerAction::create();
	if (pRockerAction)
	{
		pRockerAction->__RockerInit(strRockerImageName, strRockerImageBgName, stPoint);
		return pRockerAction;
	}
	CC_SAFE_DELETE(pRockerAction);
	return NULL;
}

void CRockerAction::StartRockerAction(bool bStopRockerAction)
{
	if (!m_pEventDispatcher)
	{
		m_pEventDispatcher = Director::getInstance()->getEventDispatcher();
	}
	
	CCSprite* pSprite = (CCSprite*)this->getChildByTag(En_Rocker);
	if (!pSprite)
	{
		CCLOG("当前 %d 层 摇杆为：", En_Rocker);
		return;
	}

	pSprite->setVisible(true);

	CCSprite* pSpriteBg = (CCSprite*)this->getChildByTag(En_RockerBg);
	if (!pSpriteBg)
	{
		CCLOG("当前 %d 层 摇杆为：", En_Rocker);
		return;
	}
	pSpriteBg->setVisible(true);
	if (!m_pEventTouchListener)
	{
		m_pEventTouchListener = EventListenerTouchOneByOne::create();
	}
	
	m_pEventTouchListener->setSwallowTouches(true);

	m_pEventTouchListener->onTouchBegan = CC_CALLBACK_2(CRockerAction::onTouchBegan, this);
	m_pEventTouchListener->onTouchMoved = CC_CALLBACK_2(CRockerAction::onTouchMoved, this);
	m_pEventTouchListener->onTouchEnded = CC_CALLBACK_2(CRockerAction::onTouchEnded, this);
	
	// 注册 触摸 事件 分发器
	m_pEventDispatcher->addEventListenerWithSceneGraphPriority(m_pEventTouchListener, this);
	//m_pEventDispatcher->addEventListenerWithSceneGraphPriority(m_pEventTouchListener, pSprite);
	//m_pEventDispatcher->addEventListenerWithSceneGraphPriority(m_pEventTouchListener->clone(), pSpriteBg);
}

void CRockerAction::StopRockerAction()
{
	CCSprite* pSprite = (CCSprite*)this->getChildByTag(En_Rocker);
	if (!pSprite)
	{
		CCLOG("当前 %d 层 摇杆为：", En_Rocker);
		return;
	}

	pSprite->setVisible(false);

	CCSprite* pSpriteBg = (CCSprite*)this->getChildByTag(En_RockerBg);
	if (!pSpriteBg)
	{
		CCLOG("当前 %d 层 摇杆为：", En_Rocker);
		return;
	}
	pSpriteBg->setVisible(false);

	if (!m_pEventDispatcher)
	{
		m_pEventDispatcher = Director::getInstance()->getEventDispatcher();
	}

	m_pEventDispatcher->removeEventListenersForTarget(this);
	//m_pEventDispatcher->removeEventListener();
}

bool CRockerAction::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	//auto pTarget = static_cast<CCSprite*>(pEvent->getCurrentTarget());
	auto pTarget = static_cast<CCSprite*>(this->getChildByTag(En_Rocker));

	// Get Point
	Point oLocNode = pTouch->getLocation();

	if (pTarget->boundingBox().containsPoint(oLocNode))
	{
		log("sprite begins..., locx: %f, locy: %f", oLocNode.x, oLocNode.y);
		m_bCanMove = true;
		return true;
	}
	return false;
}

void CRockerAction::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	if (!m_bCanMove)
	{
		return;
	}

	CCPoint stPoint = pTouch->getLocation();
	CCSprite* pTarget = static_cast<CCSprite*>(this->getChildByTag(En_Rocker));

	// get rocker and screen angle
	float fRockerAndScreenAngle = __GetRockerAndScreenAngle(m_oRockerBgPoint, stPoint);
	float fDistance = sqrt(pow((m_oRockerBgPoint.x - stPoint.x), 2) + pow((m_oRockerBgPoint.y - stPoint.y), 2));
	// distance >= Bg Radius
	if (fDistance >= m_fRockerBgRadius)
	{
		pTarget->setPosition(ccpAdd(getAnglePosition(m_fRockerBgRadius, fRockerAndScreenAngle), ccp(m_oRockerBgPoint.x, m_oRockerBgPoint.y)));
		log("Touching....");
	}
	else
	{
		pTarget->setPosition(stPoint);
	}

	CCLOG("current Rocker angle: %lf", fRockerAndScreenAngle);

	if (fRockerAndScreenAngle >= (-PI/4) && fRockerAndScreenAngle < (PI/4))
	{
		m_nRockerDirection = EnRocker_Right;
		m_bPersonRunDirection = false;
		CCLOG("turn Right: %d", m_nRockerDirection);
	}
	else if (fRockerAndScreenAngle >= (PI/4) && fRockerAndScreenAngle < (3*PI/4))
	{
		m_nRockerDirection = EnRocker_Up;
		CCLOG("turn Up: %d", m_nRockerDirection);
	}
	else if ((fRockerAndScreenAngle >= (3*PI/4) && fRockerAndScreenAngle <= PI) || 
		(fRockerAndScreenAngle >= (-PI) && fRockerAndScreenAngle < (-3*PI/4)))
	{
		m_nRockerDirection = EnRocker_Left;
		m_bPersonRunDirection = true;
		CCLOG("turn left: %d", m_nRockerDirection);
	}
	else if (fRockerAndScreenAngle >= (-3*PI/4) && fRockerAndScreenAngle < (PI/4))
	{
		m_nRockerDirection = EnRocker_Down;
		CCLOG("turn down: %d", m_nRockerDirection);
	}
}

void CRockerAction::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	if (!m_bCanMove)
	{
		return;
	}


	CCSprite* pSprite = static_cast<CCSprite*>(this->getChildByTag(En_Rocker));
	if (!pSprite)
	{
		return;
	}

	CCSprite* pSpriteBg = static_cast<CCSprite*>(this->getChildByTag(En_RockerBg));
	if (!pSpriteBg)
	{
		return;
	}

	pSprite->stopAllActions();
	pSprite->runAction(CCMoveTo::create(0.08f, pSpriteBg->getPosition()));
	m_bCanMove = false;
	m_nRockerDirection = EnRocker_Stay;
	log("Touch ends...");
	log("Rocker Direction: %d",m_nRockerDirection);
}

cocos2d::CCPoint CRockerAction::getAnglePosition(float fHepotenuse, float fAngle)
{
	return ccp(fHepotenuse*cos(fAngle), fHepotenuse*sin(fAngle));
}

void CRockerAction::__RockerInit(const char* strRockerImageName, const char* strRockerImageBgName, cocos2d::CCPoint stPoint)
{
	CCSprite* pSpriteBg = CCSprite::create(strRockerImageBgName);
	if (!pSpriteBg)
	{
		CCLOG("背景 精灵 创建 失败. 背景为：%s", strRockerImageBgName);
		return;
	}

	pSpriteBg->setPosition(stPoint);
	pSpriteBg->setVisible(false);
	addChild(pSpriteBg, 0, En_RockerBg);

	CCSprite* pSprite = CCSprite::create(strRockerImageName);
	if (!pSprite)
	{
		CCLOG("摇杆图片 加载失败， 图片为: %s", strRockerImageName);
		return;
	}

	pSprite->setPosition(stPoint);
	pSprite->setVisible(false);
	addChild(pSprite, 1, En_Rocker);

	m_oRockerBgPoint = stPoint;
	m_fRockerBgRadius = pSpriteBg->getContentSize().width*0.5;
	m_nRockerDirection = -1;	// 方向 不做改变
}

float CRockerAction::__GetRockerAndScreenAngle(cocos2d::CCPoint oFirstPoint, cocos2d::CCPoint oSecPoint)
{
	float fFirstPosLocx = oFirstPoint.x;
	float fFirstPosLocy = oFirstPoint.y;

	CCLOG("fx: %lf, fy:%lf", fFirstPosLocx, fFirstPosLocy);
	float fSecPosLocx = oSecPoint.x;
	float fSecPosLocy = oSecPoint.y;

	CCLOG("Sx: %lf, Sy:%lf", fSecPosLocx, fSecPosLocy);

	float fDistance_X = fSecPosLocx - fFirstPosLocx;
	float fDistance_Y = fSecPosLocy - fFirstPosLocy;

	// a and b hepotenuse distence
	float fhepotenuse = sqrt(pow(fDistance_X, 2) + pow(fDistance_Y, 2));
	// Calc  Cos value 
	float fCosVal = fDistance_X/fhepotenuse;

	float fCosAngle = acos(fCosVal);
	if (fDistance_Y < 0)
	{
		fCosAngle = -fCosAngle;
	}
	return fCosAngle;
}
