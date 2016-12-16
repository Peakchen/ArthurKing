
#include "SH_Yellow_Star.h"
#include "Entity\PersonPart.h"
#include "EntityProp.h"

CSH_Yellow_Star::CSH_Yellow_Star()
{
}

CSH_Yellow_Star::~CSH_Yellow_Star()
{
}

char * CSH_Yellow_Star::GetActionName()
{
	return	ETILELAYER_YELLOW_STAR;
}

void CSH_Yellow_Star::__OnEvent_Yellow_Star(CActorBase* pSelfActor)
{
	g_PersonPart.SetPersonRuleProp(pSelfActor->GetPDBID(), CREATURE_RULE_YELLOW_STAR, 2);
}

void CSH_Yellow_Star::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_YELLOW_STAR &&
		pTileLayerPeperty->szType == ETILELAYER_TYPE_DOWN)
	{

		__OnEvent_Yellow_Star(pSelfActor);
	}
}

