
#include "SH_Foot_Blue.h"
#include "Entity\PersonPart.h"
#include "EntityProp.h"

CSH_Foot_Blue::CSH_Foot_Blue()
{
}

CSH_Foot_Blue::~CSH_Foot_Blue()
{
}

char * CSH_Foot_Blue::GetActionName()
{
	return ETILELAYER_FOOT_BLUE;
}

void CSH_Foot_Blue::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_FOOT_BLUE &&
		pTileLayerPeperty->szType == ETILELAYER_TYPE_DOWN)
	{

		__OnEvent_Foot_Blue(pSelfActor);
	}
}

void CSH_Foot_Blue::__OnEvent_Foot_Blue(CActorBase* pSelfActor)
{
	g_PersonPart.SetPersonRuleProp(pSelfActor->GetPDBID(), CREATURE_RULE_FOOT_BLUE, 1);
}
