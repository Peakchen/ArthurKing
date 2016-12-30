
#include "StopThreeTimesFacade.h"
#include "Entity\PersonPart.h"
#include "PlayerManager.h"
#include "MacroDefine.h"
#include "ResCreator.h"

CStopThreeTimesFacade::CStopThreeTimesFacade()
{
}

CStopThreeTimesFacade::~CStopThreeTimesFacade()
{
}

void CStopThreeTimesFacade::OnEntityRulePropChange(int iPDBID, char* szContext)
{
	// 先扣次数
	int iCurTimes = g_PersonPart.GetPersonRuleProp(iPDBID, CREATURE_RULE_FOOT_RED);
	if (iCurTimes == 0 )
	{
		return;
	}

	g_PersonPart.SetPersonRuleProp(iPDBID, CREATURE_RULE_FOOT_RED, iCurTimes - 1);

	//执行轮空操作
	EPLAYER_ACTION iCurAction = g_PalyerManager.getRecordNextPlayerAction();
	int iNextAction = ( iCurAction % Player_Max_Count );
	iNextAction += 1;

	int iNextMsgID = arrOpenCard [iNextAction-1];
	g_ResCreator.GetPersonMessageInstance()->FireMessage(iNextMsgID, "CStopThreeTimesFacade::OnEntityRulePropChange");
}
