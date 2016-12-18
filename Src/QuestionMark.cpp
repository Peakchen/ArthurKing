#include "QuestionMark.h"
#include "common.h"
#include "GameToolAPI.h"
#include "PlayerManager.h"
#include "ResCreator.h"

CQuestionMark::CQuestionMark()
{

}

CQuestionMark::~CQuestionMark()
{

}

int CQuestionMark::GetRandomOneOperation()
{
	return g_GameToolAPI.GetRandomNum(EType_Max - 1);
}

void CQuestionMark::OnEnterOperation(int iOperation, int PDBID)
{
	switch (iOperation)
	{
		case EType_Score_Sub_Ten:
			{
				CActorBase* pActor = g_PalyerManager.GetActorInstace(PDBID);
				if (pActor == nullptr)
				{
					return;
				}

				GWORD iScore;
				pActor->GetOwnerSelfScore(iScore);
				if (iScore >= 10)
					pActor->SetOwnerSelfScore(iScore - 10);
			}
			break;

		case EType_Foot_Blue:
			{
				CActorBase* pActor = g_PalyerManager.GetActorInstace(PDBID);
				if (pActor == nullptr)
				{
					return;
				}

				g_ResCreator.GetPersonMessageInstance()->FireMessage(pActor->GetNextStepEventID(), pActor->GetNextStepEventDesc().c_str());
			}
			break;

		default:
			break;
	}
}
