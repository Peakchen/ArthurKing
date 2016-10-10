#include "PlayerManager.h"

CPlayerManager g_PalyerManager;

void CPlayerManager::DoChangeState(EPLAYER_ACTION nState)
{
	if (m_pActorBase != NULL)
	{
		m_pActorBase->OnLeave();
	}

	switch (nState)
	{
		case EACTOR_PLAYER_ACTION:
			{
				m_pActorBase = &m_oArthur;
			}
			break;
		case EAI_PLAYER_ACTION:
			{
				m_pActorBase = &m_oAiPlayer;
			}
			break;
		default:
			CCLOG("error: %s action is wrong...", __FUNCTION__);
			break;
	}

	if (m_pActorBase)
	{
		m_pActorBase->OnEnter();
	}
}

void CPlayerManager::Release()
{
	CC_SAFE_DELETE(m_pActorBase);
	m_pActorBase = NULL;
}

void CPlayerManager::Create(CActorBase* pActor)
{
	m_pActorBase = pActor;

	m_CurPlayerAction = EACTOR_PLAYER_ACTION;
	m_NextPlayerAction = EAI_PLAYER_ACTION;
}

CPlayerManager::CPlayerManager()
{

}

CPlayerManager::~CPlayerManager()
{

}

