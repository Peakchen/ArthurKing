#include "SH_OtherActionInvalid.h"
#include "PlayerManager.h"
#include "common.h"
#include "EntityProp.h"
#include "Entity\PersonPart.h"
#include "ResCreator.h"

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

void CSH_OtherActionInvalid::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	// �����ж�
	if (pTileLayerPeperty->szName == ETILELAYER_TUEN_FREE &&
		pTileLayerPeperty->iTimes == 1 && pTileLayerPeperty->szType == ETILELAYER_TYPE_UP)
	{
		// TODO:
		// ִ���ö����ֿ�һ��
		__AllowOpponentBye(pOtherActors);
	}
}

void CSH_OtherActionInvalid::__AllowOpponentBye(TActorTileLayerInfoMap* pOtherActors)
{
	FOR_EACH_CONTAINER(TActorTileLayerInfoMap, (*pOtherActors), it)
	{
		g_PersonPart.SetPersonRuleProp(it->first, CREATURE_RULE_TURN_FREE, 1);
		CActorBase* pActor = g_PalyerManager.GetActorInstace(it->first);
		if (pActor == nullptr)
		{
			Trace_In("error: no find this instance.");
			continue;
		}

		// �����ֿգ�ֱ���Լ�����
		g_ResCreator.GetPersonMessageInstance()->FireMessage(pActor->GetNextStepEventID(), pActor->GetNextStepEventDesc().c_str());
	}
}
