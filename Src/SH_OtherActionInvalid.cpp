#include "SH_OtherActionInvalid.h"
#include "PlayerManager.h"

CSH_OtherActionInvalid::CSH_OtherActionInvalid()
{

}

CSH_OtherActionInvalid::~CSH_OtherActionInvalid()
{

}

char* CSH_OtherActionInvalid::GetActionName()
{
	return "Turn_Free";
}

void CSH_OtherActionInvalid::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorInstanceMap* pOtherActors)
{
	
}
