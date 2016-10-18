#include "GiveTipAction.h"
#include "common.h"
#include "ActorBase.h"
#include "PlayerManager.h"

bool CGiveTipAction::CheckCanGiveTipToOthers(int iSeaBar_Index, CActorBase* pActor)
{
	TSeaBarInfo* pSeaBarInfo = g_SealBarManager.GetSeaBarInfo(iSeaBar_Index);
	if (pSeaBarInfo == NULL)
	{
		return false;
	}

	assert(pActor == NULL);

	__int8 Buyer_DBID = pActor->GetPDBID();

	// about sea bar, who is owner?
	if (pSeaBarInfo->iCur_OwnerID == 0)
	{
		return false;
	}
	else if (pSeaBarInfo->iCur_OwnerID != Buyer_DBID)
	{
		return true;
	}
	else if (pSeaBarInfo->iCur_OwnerID == Buyer_DBID)
	{
		return false;
	}

	return true;
}

void CGiveTipAction::DoGiveTipToOther(int iSeaBar_Index, CActorBase* pActor)
{
	TSeaBarInfo* pSeaBarInfo = g_SealBarManager.GetSeaBarInfo(iSeaBar_Index);
	if (pSeaBarInfo == NULL)
	{
		Trace_In("error: %s get TSeaBarInfo instance fail...", __FUNCTION__);
		return;
	}

	assert(pActor == NULL);

	__int8 BuyerPDBID = pSeaBarInfo->iCur_OwnerID;
	CActorBase* pBuyer = g_PalyerManager.GetActorInstace(BuyerPDBID);
	if (pBuyer == NULL)
	{
		Trace_In("error: %s get buyer instance fail...", __FUNCTION__);
		return;
	}

	GWORD gw_oldBuyScore = 0;
	pBuyer->GetOwnerSelfScore(gw_oldBuyScore);

	GWORD gw_passerOldScore = 0;
	pActor->GetOwnerSelfScore(gw_passerOldScore);

	// first spend passer some scores
	GWORD gw_passerNewScore = gw_passerOldScore - pSeaBarInfo->iTip;
	pActor->SetOwnerSelfScore(gw_passerNewScore);
	
	// then add tips to ownerself.
	GWORD gw_curBuyerScore = gw_oldBuyScore + pSeaBarInfo->iTip;
	pBuyer->SetOwnerSelfScore(gw_curBuyerScore);
}

