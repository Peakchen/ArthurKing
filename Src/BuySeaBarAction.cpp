#include "common.h"
#include "BuySeaBarAction.h"
#include "SeaBarInfoManager.h"
#include "ActorBase.h"
#include "Entity\PersonPart.h"
#include "EntityProp.h"

bool CBuySeaBarAction::CheckCanExchangeSeaBar(int iSeaBarIndex, ESeaBarAttach& attchFlag, CActorBase* pActor)
{
	TSeaBarInfo* pSeaBarInfo = g_SealBarManager.GetSeaBarInfo(iSeaBarIndex);
	if (pSeaBarInfo == NULL)
	{
		attchFlag = ESeaBar_None;
		return false;
	}

	// about sea bar, who is owner?
	if (pSeaBarInfo->iCur_OwnerID == 0)
	{
		attchFlag = ESeaBar_None;
	}
	else if (pSeaBarInfo->iCur_OwnerID != pActor->GetPDBID())
	{
		attchFlag = ESeaBar_other;
		return false;
	}
	else if (pSeaBarInfo->iCur_OwnerID == pActor->GetPDBID())
	{
		attchFlag = ESeaBar_self;
		return false;
	}

	if (pActor == NULL)
	{
		Trace_In("error: %s --- actor instance is NULL.", __FUNCTION__);
		return false;
	}

	GWORD dw_score;
	pActor->GetOwnerSelfScore(dw_score);
	// socre is enough?
	if (dw_score < pSeaBarInfo->iCur_Score)
	{
		return false;
	}

	//规则属性判断		遇到火星，之后不能购买土地，踩到分数无效，共两次
	int iYTimes = g_PersonPart.GetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_YELLOW_STAR);
	if (iYTimes > 0 )
	{
		g_PersonPart.SetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_YELLOW_STAR, iYTimes - 1);	//每执行一次，-1
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

	//TODO:
	//规则属性：是否能够购买土地
	int iYellowStarValue = g_PersonPart.GetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_YELLOW_STAR);
	if (iYellowStarValue > 0 )
	{
		g_PersonPart.SetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_YELLOW_STAR, iYellowStarValue - 1);
		// 购买无效直接返回
		return;
	}

	//TODO:
	// 判断属性规则： 购买土地是否免费
	int iBlueStarValue = g_PersonPart.GetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_BLUE_STAR);
	if (iBlueStarValue > 0)
	{
		// 属性修改
		g_PersonPart.SetPersonRuleProp(pActor->GetPDBID(), CREATURE_RULE_BLUE_STAR, iBlueStarValue-1);
	}
	else
	{
		GWORD dw_score;
		pActor->GetOwnerSelfScore(dw_score);

		// spend score at it.
		GWORD dw_resultScore = dw_score - pSeaBarInfo->iCur_Score;
		pActor->SetOwnerSelfScore(dw_resultScore);
	}

	// then make it remember who is owner...
	g_SealBarManager.SetSeaBarOwnerInfo(iSeaBarIndex, pActor->GetPDBID());
}

