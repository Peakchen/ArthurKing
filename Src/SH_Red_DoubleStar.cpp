#include "SH_Red_DoubleStar.h"
#include "EntityProp.h"
#include "Entity\PersonPart.h"

CSH_Red_DoubleStar::CSH_Red_DoubleStar()
{
}

CSH_Red_DoubleStar::~CSH_Red_DoubleStar()
{
}

char * CSH_Red_DoubleStar::GetActionName()
{
	return ETILELAYER_RED_DOUBLESTAR;
}

void CSH_Red_DoubleStar::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_RED_DOUBLESTAR &&
		pTileLayerPeperty->szType == ETILELAYER_TYPE_RANDOM)
	{

		__OnEvent_Red_DoubleStar(pSelfActor);
	}
}

void CSH_Red_DoubleStar::__OnEvent_Red_DoubleStar(CActorBase* pSelfActor)
{
	g_PersonPart.SetPersonRuleProp(pSelfActor->GetPDBID(), CREATURE_RULE_RED_DOUBLESTAR, 3);
}
