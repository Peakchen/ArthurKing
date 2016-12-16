#include "SH_OnceAgain.h"
#include "EntityProp.h"
#include "Entity\PersonPart.h"

CSH_OnceAgain::CSH_OnceAgain()
{
}

CSH_OnceAgain::~CSH_OnceAgain()
{
}

char * CSH_OnceAgain::GetActionName()
{
	return ETILELAYER_ONCEAGAIN;
}

void CSH_OnceAgain::__OnEvent_OnceAgain(CActorBase* pSelfActor)
{
	g_PersonPart.SetPersonRuleProp(pSelfActor->GetPDBID(), CREATURE_RULE_QUESTION, 1);
}

void CSH_OnceAgain::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_ONCEAGAIN &&
		pTileLayerPeperty->szType == ETILELAYER_TYPE_RANDOM)
	{

		__OnEvent_OnceAgain(pSelfActor);
	}
}
