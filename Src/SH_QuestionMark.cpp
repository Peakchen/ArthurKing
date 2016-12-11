
#include "SH_QuestionMark.h"
#include "QuestionMark.h"

CSH_QuestionMark::CSH_QuestionMark()
{

}

CSH_QuestionMark::~CSH_QuestionMark()
{

}

char* CSH_QuestionMark::GetActionName()
{
	return ETILELAYER_QUESTION;
}

void CSH_QuestionMark::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors)
{
	if (pTileLayerPeperty->szName == ETILELAYER_QUESTION && 
		pTileLayerPeperty->szType == ETILELAYER_TYPE_RANDOM)
	{
		__DealWithRandomAction(pTileLayerPeperty, pSelfActor);
	}
}

void CSH_QuestionMark::__DealWithRandomAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor)
{
	Trace_In("%s start...", __FUNCTION__);

	CQuestionMark oQuestionMark;
	int iOperation = oQuestionMark.GetRandomOneOperation();
	oQuestionMark.OnEnterOperation(iOperation, pSelfActor->GetPDBID());
}

