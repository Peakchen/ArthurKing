#include "ActionSpiltManager.h"
#include "SH_SeaBar.h"
#include "SH_OtherActionInvalid.h"

CActionSpiltManager g_ActionSpiltManager;

CActionSpiltManager::CActionSpiltManager()
{
	m_mapSH.clear();
}


CActionSpiltManager::~CActionSpiltManager()
{
}

void CActionSpiltManager::AddLiveMsg(CTileBase* pSH)
{
	if (pSH == nullptr)
	{
		return;
	}

	if (pSH && pSH->GetActionName() == "")
	{
		return;
	}

	m_mapSH [pSH->GetActionName()] = pSH;
}

void CActionSpiltManager::RemoveLiveMsg(CTileBase* pSH)
{
	if (pSH == nullptr)
	{
		return;
	}

	if (pSH && pSH->GetActionName() == "")
	{
		return;
	}

	m_mapSH.erase(pSH->GetActionName());
}

void CActionSpiltManager::CreateALiveMsg()
{
	AddLiveMsg(new CSH_SeaBar());
	AddLiveMsg(new CSH_OtherActionInvalid());
}

void CActionSpiltManager::ReleaseAliveMsg()
{
	m_mapSH.clear();
}
