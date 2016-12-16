#include "SH_Blue_Star.h"
#include "EntityProp.h"
#include "Entity\PersonPart.h"

CSH_Blue_Star::CSH_Blue_Star()
{
}

CSH_Blue_Star::~CSH_Blue_Star()
{
}

char* CSH_Blue_Star::GetActionName()
{
	return ETILELAYER_BLUE_STAR;
}

void CSH_Blue_Star::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_BLUE_STAR &&
		pTileLayerPeperty->szType == ETILELAYER_TYPE_UP)
	{
		__OnEvent_Blue_Star(pSelfActor);
	}
}

void CSH_Blue_Star::__OnEvent_Blue_Star(CActorBase* pSelfActor)
{
	g_PersonPart.SetPersonRuleProp(pSelfActor->GetPDBID(), CREATURE_RULE_BLUE_STAR, 2);
}
