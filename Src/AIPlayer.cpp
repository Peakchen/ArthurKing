#include "AIPlayer.h"
#include "ResCreator.h"


CAIPlayer::CAIPlayer ( )
{
	//g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(AI_START, this, "AI action");
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

CAIPlayer* CAIPlayer::CreateAIPlayer ( SpriteFrame* pFrame )
{
	CAIPlayer* pAi = new CAIPlayer();

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
