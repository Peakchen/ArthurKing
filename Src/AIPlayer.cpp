#include "AIPlayer.h"
#include "ResCreator.h"
#include "EntityProp.h"


CAIPlayer::CAIPlayer(__int8 PDBID) :m_PDBID(PDBID)
{
	m_ActorScore = 0;
	m_pCtrl = NULL;

	m_PropMap.clear();
	m_stRulePropMap.clear();
}

CAIPlayer::CAIPlayer()
{

}


CAIPlayer::~CAIPlayer ( )
{
}

void CAIPlayer::OnEnter()
{
	g_ResCreator.GetPersonMessageInstance()->FireMessage(AI_START, "AI action");
}

void CAIPlayer::OnLeave()
{
	CCLOG("AI leave...");
}

CAIPlayer* CAIPlayer::CreateAIPlayer(SpriteFrame* pFrame, __int8 PDBID)
{
	CAIPlayer* pAi = new CAIPlayer(PDBID);

	if (pAi && pAi->initWithSpriteFrame ( pFrame ))
	{
		pAi->autorelease ( );
		return pAi;
	}

	CC_SAFE_DELETE ( pAi );
	return NULL;
}

void CAIPlayer::RequestActorCtrl()
{
	m_pCtrl = CArthurKingControl::create();
	if (m_pCtrl == NULL)
	{
		return;
	}

	addChild(m_pCtrl);

	m_pCtrl->InitData(m_passRowPath, m_passColPath, this);
}

void CAIPlayer::UpdateScoreItem(int addScore)
{
	m_ActorScore += addScore;
}

void CAIPlayer::PlayStartGo()
{
	m_pCtrl->StartActorGo();
}

void CAIPlayer::GetOwnerSelfScore(GWORD& score)
{
	score = 0;
	score = m_ActorScore;
}

void CAIPlayer::SetOwnerSelfScore(GWORD score)
{
	m_ActorScore = score;
}

__int8 CAIPlayer::GetPDBID()
{
	return m_PDBID;
}

void CAIPlayer::AddScore(GWORD iaddScore)
{
	m_ActorScore += iaddScore;
}

void CAIPlayer::SubScore(GWORD iSubScore)
{
	m_ActorScore -= iSubScore;
}

void CAIPlayer::SetActorProp(int tyPropID, int iPropValue)
{
	TActorPropMap::iterator it = m_PropMap.find(tyPropID);
	if (it != m_PropMap.end())
	{
		return;
	}

	m_PropMap [tyPropID] = iPropValue;
}

int CAIPlayer::GetActorProp(int tyPropID)
{
	TActorPropMap::iterator it = m_PropMap.find(tyPropID);
	if (it == m_PropMap.end())
	{
		return INVALID_PROP_VALUE;
	}

	return m_PropMap [tyPropID];
}

int CAIPlayer::GetEntityPDBID()
{
	return this->GetActorProp(CREATURE_PROP_PDBID);
}

int CAIPlayer::GetEntityRuleProp(int iRulePropID)
{
	if (iRulePropID <= CREATURE_RULE_ID ||
		iRulePropID >= CREATURE_RULE_MAX)
	{
		return INVALID_RULE_VALUE;
	}

	return m_stRulePropMap [iRulePropID];
}

int CAIPlayer::GetNextStepEventID()
{
	return AI_START;
}

std::string CAIPlayer::GetNextStepEventDesc()
{
	return "AIPlayer";
}
