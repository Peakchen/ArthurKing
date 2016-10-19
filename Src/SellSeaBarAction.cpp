#include "SellSeaBarAction.h"
#include "SeaBarInfoManager.h"


CSellSeaBarAction::CSellSeaBarAction()
{
}


CSellSeaBarAction::~CSellSeaBarAction()
{
}

bool CSellSeaBarAction::CheckCanSellSeaBar(int iSeaBar_Index, CActorBase* pOwner)
{
	TSeaBarInfo* pSeaBarInfo = g_SealBarManager.GetSeaBarInfo(iSeaBar_Index);
	if (pSeaBarInfo == NULL)
	{
		return false;
	}

	if (pOwner == NULL)
	{
		return false;
	}

	if (pSeaBarInfo->iCur_OwnerID == pOwner->GetPDBID())
	{
		return true;
	}

	return false;
}

bool CSellSeaBarAction::DoSellSeaBarAction(int iSeaBar_Index, CActorBase* pOwner)
{
	if (g_SealBarManager.SellSeaBarforScore(iSeaBar_Index, pOwner))
	{
		return true;
	}

	return false;
}

