#include "SH_StopThreeTimes.h"
#include "Entity\PersonPart.h"
#include "EntityProp.h"

CSH_StopThreeTimes::CSH_StopThreeTimes()
{
}

CSH_StopThreeTimes::~CSH_StopThreeTimes()
{
}

char* CSH_StopThreeTimes::GetActionName()
{
	return	ETILELAYER_FOOT_RED;
}

void CSH_StopThreeTimes::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_FOOT_RED &&
		pTileLayerPeperty->szType == ETILELAYER_TYPE_DOWN)
	{
		__OnStopThreeTimesAction(pSelfActor);
	}
}

void CSH_StopThreeTimes::__OnStopThreeTimesAction(CActorBase* pSelfActor)
{
	g_PersonPart.SetPersonRuleProp(pSelfActor->GetPDBID(), CREATURE_RULE_FOOT_RED, 3);
}
