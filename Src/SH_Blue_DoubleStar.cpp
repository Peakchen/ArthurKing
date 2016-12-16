#include "SH_Blue_DoubleStar.h"
#include "Entity\PersonPart.h"
#include "EntityProp.h"

CSH_Blue_DoubleStar::CSH_Blue_DoubleStar()
{
}

CSH_Blue_DoubleStar::~CSH_Blue_DoubleStar()
{
}

char* CSH_Blue_DoubleStar::GetActionName()
{
	return ETILELAYER_BLUE_DOUBLESTAR;
}

void CSH_Blue_DoubleStar::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_BLUE_DOUBLESTAR &&
		pTileLayerPeperty->szType == ETILELAYER_TYPE_UP)
	{
		
		__OnEvent_Blue_DoubleStar(pSelfActor);
	}
}

void CSH_Blue_DoubleStar::__OnEvent_Blue_DoubleStar(CActorBase* pSelfActor)
{
	g_PersonPart.SetPersonRuleProp(pSelfActor->GetPDBID(), CREATURE_RULE_BLUE_DOUBLESTAR, 3);
}
