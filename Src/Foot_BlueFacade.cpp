
#include "Foot_BlueFacade.h"
#include "Entity\PersonPart.h"
#include "EntityProp.h"
#include "PlayerManager.h"
#include "MacroDefine.h"
#include "ResCreator.h"

CFoot_BlueFacade::CFoot_BlueFacade()
{
}

CFoot_BlueFacade::~CFoot_BlueFacade()
{
}

void CFoot_BlueFacade::OnEntityRulePropChange(int iPDBID, char* szContext)
{
	CCLOG("%s is exec.", __FUNCTION__);

	int iFootBlueTimes = g_PersonPart.GetPersonRuleProp(iPDBID, CREATURE_RULE_FOOT_BLUE);
	if (iFootBlueTimes > 0)
	{
		iFootBlueTimes -= 1;
	}

	EPLAYER_ACTION iCurAction = g_PalyerManager.getRecordNextPlayerAction();
	int iNextAction = ( iCurAction % Player_Max_Count );
	iNextAction += 1;

	int iNextMsgID = arrOpenCard [iNextAction - 1];
	g_ResCreator.GetPersonMessageInstance()->FireMessage(iNextMsgID, "CFoot_BlueFacade::OnEntityRulePropChange");
}
