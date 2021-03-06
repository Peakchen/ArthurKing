#include "ArthurKing.h"
#include "ConstUtil.h"
#include "MapReader.h"
#include "ArthurKingControl.h"
#include "ResCreator.h"
#include "common.h"
#include "EntityProp.h"

USING_NS_CC;

CArthurKing::CArthurKing(__int8 PDBID) :m_PDBID(PDBID)
{
	m_ActorScore = 0;
	m_pCtrl = NULL;

	m_bCheckActorRuning = false;
	m_bActorRunDirector = false;
	m_pActorSprite = NULL;
	m_szSpriteName = NULL;

	m_PropMap.clear();
	m_stRulePropMap.clear();
	//g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(AI_START, this, "player action");
}

CArthurKing::CArthurKing()
{

}


CArthurKing::~CArthurKing()
{
}

CArthurKing* CArthurKing::CreateArthurKing(SpriteFrame* pFrame, __int8 PDBID)
{
	CArthurKing* pArthur = new CArthurKing(PDBID);

	if (pArthur && pArthur->initWithSpriteFrame(pFrame))
	{
		pArthur->autorelease();
		return pArthur;
	}

	CC_SAFE_DELETE(pArthur);
	return NULL;
}

void CArthurKing::RequestActorCtrl()
{
	
	m_pCtrl = CArthurKingControl::create();
	if (m_pCtrl == NULL)
	{
		return;
	}
	
	addChild(m_pCtrl);

	m_pCtrl->InitData(m_passRowPath, m_passColPath, this);
}

void CArthurKing::PlayStartGo()
{
	m_pCtrl->StartActorGo();
}

void CArthurKing::UpdateScoreItem ( int addScore )
{
	m_ActorScore += addScore;
}

void CArthurKing::OnEnter ( )
{
	g_ResCreator.GetPersonMessageInstance()->FireMessage(ACTOR_START, "player action");
}

void CArthurKing::OnLeave()
{
	CCLOG("ArthurKing leave...");
}

void CArthurKing::GetOwnerSelfScore(GWORD& score)
{
	score = 0;
	score = m_ActorScore;
}

void CArthurKing::SetOwnerSelfScore(GWORD score)
{
	m_ActorScore = score;
}

__int8 CArthurKing::GetPDBID()
{
	return m_PDBID;
}

void CArthurKing::AddScore(GWORD iaddScore)
{
	m_ActorScore += iaddScore;
}

void CArthurKing::SubScore(GWORD iSubScore)
{
	m_ActorScore -= iSubScore;
}

void CArthurKing::SetActorProp(int tyPropID, int iPropValue)
{
	TActorPropMap::iterator it = m_PropMap.find(tyPropID);
	if (it != m_PropMap.end())
	{
		return;
	}

	m_PropMap [tyPropID] = iPropValue;
}

int CArthurKing::GetActorProp(int tyPropID)
{
	TActorPropMap::iterator it = m_PropMap.find(tyPropID);
	if (it == m_PropMap.end())
	{
		return INVALID_PROP_VALUE;
	}

	return m_PropMap [tyPropID];
}

int CArthurKing::GetEntityPDBID()
{
	return this->GetActorProp(CREATURE_PROP_PDBID);
}

int CArthurKing::GetEntityRuleProp(int iRulePropID)
{
	if (iRulePropID <= CREATURE_RULE_ID ||
			iRulePropID >= CREATURE_RULE_MAX)
	{
		return INVALID_RULE_VALUE;
	}

	return m_stRulePropMap [iRulePropID];
}

int CArthurKing::GetNextStepEventID()
{
	return ACTOR_START;
}

std::string CArthurKing::GetNextStepEventDesc()
{
	return "ArthurKing";
}
