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
	// ��ǰ��ɫ�ٴη��ƣ�ֱ��ȥ���Ƽ���
	g_ResCreator.GetPersonMessageInstance()->FireMessage(iEventID, "COnceAgainFacade::OnEntityRulePropChange");
}
