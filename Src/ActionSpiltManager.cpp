#include "ActionSpiltManager.h"
#include "SH_SeaBar.h"
#include "SH_OtherActionInvalid.h"
#include "SH_QuestionMark.h"
#include "SH_Blue_DoubleStar.h"
#include "SH_Blue_Star.h"
#include "SH_Foot_Blue.h"
#include "SH_StopThreeTimes.h"
#include "SH_OnceAgain.h"
#include "SH_Red_DoubleStar.h"
#include "SH_Yellow_Star.h"

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
	AddLiveMsg(new CSH_QuestionMark());
	AddLiveMsg(new CSH_Blue_DoubleStar());
	AddLiveMsg(new CSH_Blue_Star());
	AddLiveMsg(new CSH_Foot_Blue());
	AddLiveMsg(new CSH_StopThreeTimes());
	AddLiveMsg(new CSH_OnceAgain());
	AddLiveMsg(new CSH_QuestionMark());
	AddLiveMsg(new CSH_Red_DoubleStar());
	AddLiveMsg(new CSH_Yellow_Star());
}

void CActionSpiltManager::ReleaseAliveMsg()
{
	m_mapSH.clear();
}
