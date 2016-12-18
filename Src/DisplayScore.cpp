#include "DisplayScore.h"

CDisplayScore::CDisplayScore()
{
	m_pScoreLabel = NULL;
	m_pActor = nullptr;
}

CDisplayScore::~CDisplayScore()
{
	Release();
}

CDisplayScore* CDisplayScore::CreateDisplayScoreLabel(const char* szPng, CActorBase* pActor)
{
	CDisplayScore* pDisplayerSocre = new CDisplayScore();
	if (pDisplayerSocre && pDisplayerSocre->init()
		&& pDisplayerSocre->initScore(szPng, pActor))
	{
		pDisplayerSocre->autorelease();
		return pDisplayerSocre;
	}

	CC_SAFE_DELETE(pDisplayerSocre);
	return NULL;
}
 
void CDisplayScore::Release()
{
	CCLOG("delete this: %s", __FUNCTION__);
}

bool CDisplayScore::initScore(const char* szPng, CActorBase* pActor)
{
	if (NULL == pActor)
	{
		return false;
	}

	m_pActor = pActor;
	GWORD dwScore;
	pActor->GetOwnerSelfScore(dwScore);

	MenuItemImage* pScoreLogo = MenuItemImage::create(szPng, szPng);
	if (NULL == pScoreLogo)
	{
		return false;
	}

	pScoreLogo->setPosition(ccp(5.0f, 10.0f));
	pScoreLogo->setAnchorPoint(ccp(0.5f, 0.5f));

	char szScoreContext [10] = {0};
	sprintf(szScoreContext, "%d", dwScore);
	const string  szStrScore(szScoreContext);
	
	m_pScoreLabel = Label::createWithSystemFont(szStrScore, "Arial", 20, Size::ZERO, cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
	if (NULL == m_pScoreLabel)
	{
		CCLOG("%s is error...", __FUNCTION__);
		return false;
	}

	//m_pScoreLabel->setColor(Color3B::YELLOW);
	m_pScoreLabel->enableShadow(Color4B::GREEN, Size(10, 10));
	//m_pScoreLabel->enableOutline(Color4B::RED, 3);
	m_pScoreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_pScoreLabel->setPosition(ccp(20.0f, 3.0f));

	this->addChild(pScoreLogo);
	this->addChild(m_pScoreLabel);
	return true;
}

bool CDisplayScore::init()
{
	CCLOG("%s starts...", __FUNCTION__);
	if (!Layer::init())
	{
		CCLOG("%s is error...", __FUNCTION__);
		return false;
	}

	return true;
}

void CDisplayScore::UpdateEntityScore()
{
	CC_ASSERT(m_pActor != NULL);

	GWORD dwScore;
	m_pActor->GetOwnerSelfScore(dwScore);

	char szScoreContext [10] = { 0 };
	sprintf(szScoreContext, "%d", dwScore);

	CC_ASSERT(m_pScoreLabel != NULL);
	m_pScoreLabel->setString(szScoreContext);
}


