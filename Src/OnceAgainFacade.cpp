#include "OnceAgainFacade.h"
#include "ResCreator.h"

COnceAgainFacade::COnceAgainFacade()
{
}

COnceAgainFacade::~COnceAgainFacade()
{
}

void COnceAgainFacade::OnEntityRulePropChange(int iPDBID, char* szContext)
{
	TR_OnceAgain* szOnceAgain = reinterpret_cast< TR_OnceAgain* >( szContext );
	int iEventID = arrOpenCard [iPDBID];
	// 当前角色再次翻牌，直接去翻牌即可
	g_ResCreator.GetPersonMessageInstance()->FireMessage(iEventID, "COnceAgainFacade::OnEntityRulePropChange");
}
