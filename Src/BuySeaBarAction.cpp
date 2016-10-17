#include "common.h"
#include "BuySeaBarAction.h"
#include "SeaBarInfoManager.h"
#include "ActorBase.h"



bool CBuySeaBarAction::CheckCanExchangeSeaBar(int iSeaBarIndex, __int8 Buyer_DBID, ESeaBarAttach& attchFlag, CActorBase* pActor)
{
	TSeaBarInfo* pSeaBarInfo = g_SealBarManager.GetSeaBarInfo(iSeaBarIndex);
	if (pSeaBarInfo == NULL)
	{
		attchFlag = ESeaBar_Error;
		return false;
	}

	// about sea bar, who is owner?
	if (pSeaBarInfo->iCur_OwnerID == 0)
	{
		attchFlag = ESeaBar_None;
	}
	else if (pSeaBarInfo->iCur_OwnerID != Buyer_DBID)
	{
		attchFlag = ESeaBar_other;
		return false;
	}
	else if (pSeaBarInfo->iCur_OwnerID == Buyer_DBID)
	{
		attchFlag = ESeaBar_self;
		return false;
	}

	if (pActor == NULL)
	{
		Trace_In("error: %s --- actor instance is NULL.", __FUNCTION__);
		return false;
	}

	GWORD dw_score = 0;
	pActor->GetOwnerSelfScore(dw_score);
	// socre is enough?
	if (dw_score < pSeaBarInfo->iCur_Score)
	{
		return false;
	}
	
	return true;
}

void CBuySeaBarAction::DoExchangeSeaBar(int iSeaBarIndex, CActorBase* pActor)
{
	TSeaBarInfo* pSeaBarInfo = g_SealBarManager.GetSeaBarInfo(iSeaBarIndex);
	if (pSeaBarInfo == NULL)
	{
		Trace_In("error:%s ---- GetSeaBarInfo(iSeaBarIndex) is NULL....", __FUNCTION__);
		return;
	}

	GWORD dw_score = 0;
	pActor->GetOwnerSelfScore(dw_score);

	// spend score at it.
	GWORD dw_resultScore = dw_score - pSeaBarInfo->iCur_Score;
	pActor->SetOwnerSelfScore(dw_resultScore);

	// then make it remember who is owner...

	g_SealBarManager.SetSeaBarOwnerInfo(iSeaBarIndex, pActor->GetPDBID());
}

