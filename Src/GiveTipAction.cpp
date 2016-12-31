#include "GiveTipAction.h"
#include "PlayerManager.h"
#include "SeaBarInfoManager.h"
#include "Entity\PersonPart.h"
#include "EntityProp.h"

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

	GWORD gw_passerOldScore;
	pActor->GetOwnerSelfScore(gw_passerOldScore);

	int iGiveTips = pSeaBarInfo->iTip;

	// 判断是否当前规则属性 是否付费加倍
	int	iRedDoubleStarTimes = g_PersonPart.GetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_RED_DOUBLESTAR);
	if (iRedDoubleStarTimes > 0)
	{
		iGiveTips *= 2;
	}

	if (gw_passerOldScore < iGiveTips)
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

	GWORD gw_oldBuyScore;
	pBuyer->GetOwnerSelfScore(gw_oldBuyScore);

	GWORD gw_passerOldScore;
	pActor->GetOwnerSelfScore(gw_passerOldScore);
	
	int iGiveTips = pSeaBarInfo->iTip;

	// 判断是否当前规则属性 是否付费加倍
	int	iRedDoubleStarTimes = g_PersonPart.GetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_RED_DOUBLESTAR);
	if (iRedDoubleStarTimes > 0 )
	{
		iGiveTips *= 2;
		g_PersonPart.SetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_RED_DOUBLESTAR, iRedDoubleStarTimes-1);
	}

	if (gw_passerOldScore < iGiveTips)
	{
		CCLOG("%s 分数购买力不足，请重试。", __FUNCTION__);
		return;
	}

	// 是否免费
	int iBlueDoubleStar = g_PersonPart.GetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_BLUE_DOUBLESTAR);
	if (iBlueDoubleStar > 0 )
	{
		// 直接返回
		g_PersonPart.SetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_BLUE_DOUBLESTAR, iBlueDoubleStar - 1);
		return;
	}

	// first spend passer some scores
	GWORD gw_passerNewScore = gw_passerOldScore - iGiveTips;
	pActor->SetOwnerSelfScore(gw_passerNewScore);
	
	// then add tips to ownerself.
	GWORD gw_curBuyerScore = gw_oldBuyScore + iGiveTips;
	pBuyer->SetOwnerSelfScore(gw_curBuyerScore);
}

CGiveTipAction::CGiveTipAction()
{

}

CGiveTipAction::~CGiveTipAction()
{

}

