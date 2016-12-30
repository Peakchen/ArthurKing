#include "RuleManager.h"
#include "ResCreator.h"
#include "common.h"
#include "OnceAgainFacade.h"


CRuleManager::CRuleManager()
{
}

CRuleManager::~CRuleManager()
{

}

void CRuleManager::OnExecRuleEventMessage(int iPDBID, char* szContext, GWORD nMsgID, const char* szDesc)
{
	switch (nMsgID)
	{
		case EN_RULE_EVENT_BLUE_DOUBLE_STAR:
			{

			}
			break;
		case EN_RULE_EVENT_BLUE_STAR:
			{

			}
			break;
		case EN_RULE_EVENT_FOOT_BULE:
			{

			}
			break;
		case EN_RULE_EVENT_FOOT_RED:
			{

			}
			break;
		case EN_RULE_EVENT_ONCE_AGAIN:
			{
				COnceAgainFacade oOnceAgainFacade;
				oOnceAgainFacade.OnEntityRulePropChange(iPDBID, szContext);
			}
			break;
		case EN_RULE_EVENT_QUESTION:
			{
				
			}
			break;
		case EN_RULE_EVENT_RED_DOUBLE_STAR:
			{

			}
			break;
		case EN_RULE_EVENT_TURN_FREE:
			{

			}
			break;
		case EN_RULE_EVENT_YELLOW_STAR:
			{

			}
			break;
		default:
			log("%s: ", __FUNCTION__);
			break;
	}
}

void CRuleManager::RegisterMsgEvent()
{
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_BLUE_DOUBLE_STAR, this, ETILELAYER_BLUE_DOUBLESTAR);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_BLUE_STAR, this, ETILELAYER_BLUE_STAR);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_FOOT_BULE, this, ETILELAYER_FOOT_BLUE);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_FOOT_RED, this, ETILELAYER_FOOT_RED);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_ONCE_AGAIN, this, ETILELAYER_ONCEAGAIN);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_QUESTION, this, ETILELAYER_QUESTION);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_RED_DOUBLE_STAR, this, ETILELAYER_RED_DOUBLESTAR);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_TURN_FREE, this, ETILELAYER_TUEN_FREE);
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_EVENT_YELLOW_STAR, this, ETILELAYER_YELLOW_STAR);
}

void CRuleManager::Release()
{
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_BLUE_DOUBLE_STAR, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_BLUE_STAR, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_FOOT_BULE, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_FOOT_RED, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_ONCE_AGAIN, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_QUESTION, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_RED_DOUBLE_STAR, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_TURN_FREE, this);
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_EVENT_YELLOW_STAR, this);
}
