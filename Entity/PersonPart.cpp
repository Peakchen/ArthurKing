
#include "PersonPart.h"
#include "EntityProp.h"
#include "PlayerManager.h"
#include "ResCreator.h"

CPersonPart	 g_PersonPart;

CPersonPart::CPersonPart()
{
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(EN_RULE_PROP_EVENT, this, "规则属性事件");
}

CPersonPart::~CPersonPart()
{
	g_ResCreator.GetPersonMessageInstance()->UnRegisterAIMessage(EN_RULE_PROP_EVENT, this);
}

void CPersonPart::ImportPersonData()
{
	FOR_EACH_CONTAINER(TPersonInfoMap, ( *g_PalyerManager.GetActorLocInfo() ), itActor)
	{
		__InitPersonRulePropData(itActor->first);
		__InitPersonSelfPropData(itActor->first);
	}
}

void CPersonPart::ExportPersonData()
{
	//g_PalyerManager.SavePersonInfoData();
}

void CPersonPart::OnExecMessageHandle(GWORD nMsgID, const char* szDesc)
{
	switch (nMsgID)
	{
		case EN_RULE_PROP_EVENT:
			{
				// do something

			}
			break;
		default:
			log("file: %s, function:%s is error.",__FILE__ ,__FUNCTION__);
			break;
	}
}

void CPersonPart::__InitPersonRulePropData(int PDBID)
{

	//SetPersonRuleProp(PDBID, CREATURE_RULE_ID, 0);	//不必赋值	不必赋值	不必赋值

	////////////////////////////////导入规则数据//////////////////////////////////

	SetPersonRuleProp(PDBID, CREATURE_RULE_ONCE_AGAIN, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_TURN_FREE, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_QUESTION, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_FOOT_RED, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_YELLOW_STAR, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_RED_DOUBLESTAR, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_FOOT_BLUE, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_BLUE_STAR, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_BLUE_DOUBLESTAR, 0);
}

void CPersonPart::__InitPersonSelfPropData(int PDBID)
{
	////////////////////////////////导入角色数据/////////////////////////////
	SetPersonProp(PDBID, CREATURE_PROP_PDBID, PDBID);
}

int CPersonPart::GetPersonRuleProp(int PDBID, int iRulePropID)
{
	if (iRulePropID <= CREATURE_RULE_ID ||
		iRulePropID >= CREATURE_RULE_MAX)
	{
		return INVALID_RULE_VALUE;
	}

	TRuleSinglePropMap pstmap_RuleSingleProp = m_stRuleProp [PDBID];
	TRuleProp stProp = pstmap_RuleSingleProp [iRulePropID];

	return stProp.iRulePropValue;
}

void CPersonPart::SetPersonRuleProp(int PDBID, int iRulePropID, int iValue)
{
	if (iRulePropID <= CREATURE_RULE_ID ||
		iRulePropID >= CREATURE_RULE_MAX)
	{
		Trace_In("error: %s 错误的规则属性ID.", __FUNCTION__);
		return;
	}

	if (INVALID_MAX_VALUE < iValue || 
		iValue < INVALID_RULE_VALUE)
	{
		Trace_In("error: %s 错误的规则属性值.", __FUNCTION__);
		return;
	}
	
	TRuleSinglePropMap& pstmap_RuleSingleProp = m_stRuleProp [PDBID];
	TRuleProp& stProp = pstmap_RuleSingleProp [iRulePropID];

	TRuleProp stRuleProp;
	stRuleProp.iRulePropID = iRulePropID;
	stRuleProp.iRulePropValue = iValue;
	stProp = stRuleProp;
}

int CPersonPart::GetPersonProp(int PDBID, int iPropID)
{
	if (iPropID <= CREATURE_RULE_ID ||
		iPropID >= CREATURE_RULE_MAX)
	{
		return INVALID_RULE_VALUE;
	}
	
	TPersonSinglePropMap stmap_PersonSingleProp = m_stNumProp [PDBID];
	const TPersonProp stProp = stmap_PersonSingleProp [iPropID];
	return stProp.iValue;
}

void CPersonPart::SetPersonProp(int PDBID, int iPropID, int iValue)
{
	if (iPropID <= CREATURE_RULE_ID ||
		iPropID >= CREATURE_RULE_MAX)
	{
		Trace_In("error: %s 错误的规则属性ID.", __FUNCTION__);
		return;
	}

	if (INVALID_MAX_VALUE < iValue ||
		iValue >= INVALID_RULE_VALUE)
	{
		Trace_In("error: %s 错误的规则属性值.", __FUNCTION__);
		return;
	}

	TPersonSinglePropMap& stmap_PersonSingleProp = m_stNumProp [PDBID];
	TPersonProp& stProp = stmap_PersonSingleProp [iPropID];

	TPersonProp stPersonProp;
	stPersonProp.iPropID = iPropID;
	stPersonProp.iValue = iValue;
	stProp = stPersonProp;
}

void CPersonPart::__OnEvent_RuleProp()
{
	CActorBase* pCurActor = g_PalyerManager.GetFinallyStepPerson();
	if (pCurActor == nullptr)
	{
		log("%s: 取得当前角色为null.", __FUNCTION__);
		return;
	}
	
	int iPDBID = pCurActor->GetPDBID();
	if( GetPersonRuleProp(iPDBID, CREATURE_RULE_ONCE_AGAIN) > 0)
	{
		TR_OnceAgain stOnceAgainContext;
		// 预留现场
		//
		char* szOnceAgain = reinterpret_cast< char* >( &stOnceAgainContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szOnceAgain, EN_RULE_EVENT_QUESTION, ETILELAYER_QUESTION);
	}

	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_TURN_FREE) > 0)
	{
		TR_Turn_Free stTurn_FreeContext;
		// 预留现场
		//
		char* szTurn_Free = reinterpret_cast< char* >( &stTurn_FreeContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szTurn_Free, EN_RULE_EVENT_TURN_FREE, ETILELAYER_TUEN_FREE);
	}

	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_QUESTION) > 0)
	{
		TR_Question stQuestionContext;
		// 预留现场
		//
		char* szQuestionContext = reinterpret_cast< char* >( &stQuestionContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szQuestionContext, EN_RULE_EVENT_QUESTION, ETILELAYER_QUESTION);
	}
	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_FOOT_RED) > 0)
	{
		TR_Foot_Red stFoot_RedContext;
		// 预留现场
		//
		char* szFoot_RedContext = reinterpret_cast< char* >( &stFoot_RedContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szFoot_RedContext, EN_RULE_EVENT_FOOT_RED, ETILELAYER_FOOT_RED);
	}

	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_YELLOW_STAR) > 0)
	{
		TR_Yellow_Star stYellow_StarContext;
		// 预留现场
		//
		char* szYellow_StarContext = reinterpret_cast< char* >( &stYellow_StarContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szYellow_StarContext, EN_RULE_EVENT_YELLOW_STAR, ETILELAYER_YELLOW_STAR);
	}

	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_RED_DOUBLESTAR) > 0)
	{
		TR_Red_DoubleStar stRed_DoubleStarContext;
		// 预留现场
		//
		char* szRed_DoubleStarContext = reinterpret_cast< char* >( &stRed_DoubleStarContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szRed_DoubleStarContext, EN_RULE_EVENT_RED_DOUBLE_STAR, ETILELAYER_RED_DOUBLESTAR);
	}

	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_FOOT_BLUE) > 0)
	{
		TR_Foot_Blue stFoot_BlueContext;
		// 预留现场
		//
		char* szFoot_BlueContext = reinterpret_cast< char* >( &stFoot_BlueContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szFoot_BlueContext, EN_RULE_EVENT_FOOT_BULE, ETILELAYER_FOOT_BLUE);
	}

	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_BLUE_STAR) > 0)
	{
		TR_Blue_Star stBlue_StarContext;
		// 预留现场
		//
		char* szBlue_StarContext = reinterpret_cast< char* >( &stBlue_StarContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szBlue_StarContext, EN_RULE_EVENT_BLUE_STAR, ETILELAYER_BLUE_STAR);
	}

	if (GetPersonRuleProp(iPDBID, CREATURE_RULE_BLUE_DOUBLESTAR) > 0)
	{
		TR_Blue_DoubleStar stBlue_DoubleStarContext;
		// 预留现场
		//
		char* szBlue_DoubleStarContext = reinterpret_cast< char* >( &stBlue_DoubleStarContext );
		g_ResCreator.GetPersonMessageInstance()->FireRulePropChangeEvent(iPDBID, szBlue_DoubleStarContext, EN_RULE_EVENT_BLUE_DOUBLE_STAR, ETILELAYER_BLUE_DOUBLESTAR);
	}
	
}

