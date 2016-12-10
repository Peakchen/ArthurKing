#include "AIPlayer.h"
#include "ResCreator.h"


CAIPlayer::CAIPlayer(__int8 PDBID) :m_PDBID(PDBID)
{
	//g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(AI_START, this, "AI action");
	m_ActorScore = 0;
	m_pCtrl = NULL;
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
		return 0;
	}

	return m_PropMap [tyPropID];
}

IEntity* CAIPlayer::GetEntityByPDBID(GWORD pdbid)
{
	return NULL;
}
